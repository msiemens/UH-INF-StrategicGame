//
// chat_server.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "chat_message.hpp"

using boost::asio::ip::tcp;
using namespace std;

//----------------------------------------------------------------------

typedef std::deque<Message> MessageQueue;

//----------------------------------------------------------------------

class NetConnection {
public:
	virtual ~NetConnection() {
	}
	virtual void Send(const Message& msg) = 0;
};

typedef boost::shared_ptr<NetConnection> NetworkClientPtr;

//----------------------------------------------------------------------

class NetGame {
public:
	void Join(NetworkClientPtr participant) {
		m_players.insert(participant);
	}

	void Leave(NetworkClientPtr participant) {
		m_players.erase(participant);
	}

	void Broadcast(const Message& msg) {
		std::for_each(m_players.begin(), m_players.end(),
				boost::bind(&NetConnection::Send, _1, boost::ref(msg)));
	}

private:
	std::set<NetworkClientPtr> m_players;
};

//----------------------------------------------------------------------

class NetPlayer: public NetConnection, public boost::enable_shared_from_this<
		NetPlayer> {
public:
	NetPlayer(boost::asio::io_service& io_service, NetGame& game) :
			m_socket(io_service), m_game(game) {
	}

	tcp::socket& socket() {
		return m_socket;
	}

	// Start listening on our socket
	void Start() {
		cout << ":: Connection established" << endl;

		m_game.Join(shared_from_this());
		_ReadHeader();
	}

	// Send a message to a player
	void Send(const Message& msg) {
		cout << "Delivering message... " << msg.data() << " ("
				<< msg.body_length() << ")" << endl;

		bool write_in_progress = !m_write_msgs.empty();
		m_write_msgs.push_back(msg);
		if (!write_in_progress) {
			_Write(m_write_msgs.front());
		}
	}

	// Handle an incoming header
	void OnHeader(const boost::system::error_code& error) {
		cout << "Recieving message... " << endl;

		if (!error && m_read_msg.decode_header()) {
			_ReadBody();
		} else {
			m_game.Leave(shared_from_this());
		}
	}

	// Handle incoming body
	void OnBody(const boost::system::error_code& error) {
		cout << "Message recieved. Broadcasting it. " << endl;

		if (!error) {
			m_game.Broadcast(m_read_msg);
			_ReadHeader();
		} else {
			m_game.Leave(shared_from_this());
		}
	}

	// OnWriteHandler
	void OnWrite(const boost::system::error_code& error) {
		cout << "Message delivered: " << m_write_msgs.front().data() << " ("
				<< m_write_msgs.front().body_length() << ")" << endl;
		if (!error) {
			m_write_msgs.pop_front();
			if (!m_write_msgs.empty()) {
				_Write(m_write_msgs.front());
			}
		} else {
			m_game.Leave(shared_from_this());
		}
	}

private:
	tcp::socket m_socket;
	NetGame& m_game;
	Message m_read_msg;
	MessageQueue m_write_msgs;

	void _Write(Message msg) {
		boost::asio::async_write(m_socket,
				boost::asio::buffer(msg.data(), msg.length()),
				boost::bind(&NetPlayer::OnWrite, shared_from_this(),
						boost::asio::placeholders::error));
	}

	void _ReadHeader() {
		boost::asio::async_read(m_socket,
				boost::asio::buffer(m_read_msg.data(), Message::header_length),
				boost::bind(&NetPlayer::OnHeader, shared_from_this(),
						boost::asio::placeholders::error));
	}

	void _ReadBody() {
		boost::asio::async_read(m_socket,
				boost::asio::buffer(m_read_msg.body(),
						m_read_msg.body_length()),
				boost::bind(&NetPlayer::OnBody, shared_from_this(),
						boost::asio::placeholders::error));
	}
};

typedef boost::shared_ptr<NetPlayer> NetPlayerPtr;

//----------------------------------------------------------------------

class GameNetworkImpl {
public:
	GameNetworkImpl(int port) :
			m_io_service(), m_endpoint(tcp::v4(), port), m_acceptor(
					m_io_service, m_endpoint) {
		// Start accepting connections
		StartAccept();

		// Run the IO service
		m_io_service.run();
	}

	// Start accepting new connections
	void StartAccept() {
		// Wait asynchronously for new connections
		NetPlayerPtr new_session(new NetPlayer(m_io_service, m_room));
		m_acceptor.async_accept(new_session->socket(),
				boost::bind(&GameNetworkImpl::HandleAccept, this, new_session,
						boost::asio::placeholders::error));
	}

	// Handle an incomming connection
	void HandleAccept(NetPlayerPtr session,
			const boost::system::error_code& error) {
		if (!error) {
			session->Start();
		}

		// Listen for more connections
		StartAccept();
	}

private:
	const tcp::endpoint m_endpoint;
	boost::asio::io_service m_io_service;
	tcp::acceptor m_acceptor;
	NetGame m_room;
};

//----------------------------------------------------------------------

int main(int argc, char* argv[]) {
	try {
		if (argc < 2) {
			std::cerr << "Usage: chat_server <port> [<port> ...]\n";
			return 1;
		}

		new GameNetworkImpl(atoi(argv[1]));

	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
