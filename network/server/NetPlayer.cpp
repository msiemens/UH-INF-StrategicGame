/*
 * NetPlayer.cpp
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#include "NetPlayer.h"

NetPlayer::NetPlayer(boost::asio::io_service& io_service, NetGame& game) :
		m_socket(io_service), m_game(game) {
}

tcp::socket& NetPlayer::socket() {
	return m_socket;
}

// Start listening on our socket
void NetPlayer::Start() {
	cout << ":: Connection established" << endl;

	m_game.Join(shared_from_this());
	_ReadHeader();
}

// Send a message to a player
void NetPlayer::Send(NetworkMessagePtr msg) {
	cout << "Delivering message..." << endl;

	bool write_in_progress = !m_write_msgs.empty();
	m_write_msgs.push_back(msg);
	if (!write_in_progress) {
		_Write(m_write_msgs.front());
	}
}

// Handle an incoming header
void NetPlayer::OnHeader(const boost::system::error_code& error) {
	cout << "Recieving message..." << endl;

	if (!error && m_read_msg->DecodeHeader()) {
		_ReadBody();
	} else {
		m_game.Leave(shared_from_this());
	}
}

// Handle incoming body
void NetPlayer::OnBody(const boost::system::error_code& error) {
	cout << "Message recieved. Broadcasting it. " << endl;

	if (!error) {
		m_game.Broadcast(m_read_msg);
		_ReadHeader();
	} else {
		m_game.Leave(shared_from_this());
	}
}

// OnWriteHandler
void NetPlayer::OnWrite(const boost::system::error_code& error) {
	cout << "Message delivered" << endl;
	if (!error) {
		m_write_msgs.pop_front();
		if (!m_write_msgs.empty()) {
			_Write(m_write_msgs.front());
		}
	} else {
		m_game.Leave(shared_from_this());
	}
}

void NetPlayer::_Write(NetworkMessagePtr msg) {
	boost::asio::async_write(m_socket,
			boost::asio::buffer(msg->data(), msg->length()),
			boost::bind(&NetPlayer::OnWrite, shared_from_this(),
					boost::asio::placeholders::error));
}

void NetPlayer::_ReadHeader() {
	boost::asio::async_read(m_socket,
			boost::asio::buffer(m_read_msg->data(),
					NetworkMessage::header_length),
			boost::bind(&NetPlayer::OnHeader, shared_from_this(),
					boost::asio::placeholders::error));
}

void NetPlayer::_ReadBody() {
	boost::asio::async_read(m_socket,
			boost::asio::buffer(m_read_msg->body(), m_read_msg->body_length()),
			boost::bind(&NetPlayer::OnBody, shared_from_this(),
					boost::asio::placeholders::error));
}
