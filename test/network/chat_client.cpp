//
// chat_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <deque>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "chat_message.hpp"

using boost::asio::ip::tcp;

typedef std::deque<Message> MessageQueue;

// The API layer providing abstraction for the boost methods.
class ClientNetworkImpl {
public:
	ClientNetworkImpl(char* host, char* port) :
			m_io_service(), m_socket(m_io_service), m_tcp_resolver(
					m_io_service), m_tcp_query(host, port), m_tcp_endpoint_iterator(
					m_tcp_resolver.resolve(m_tcp_query)) {

		// After init, listen for new connections and run handle_connect
		boost::asio::async_connect(m_socket, m_tcp_endpoint_iterator,
				boost::bind(&ClientNetworkImpl::OnConnect, this,
						boost::asio::placeholders::error));

		// Start the IO thread
		m_thread = boost::thread(
				boost::bind(&boost::asio::io_service::run, &m_io_service));
	}

	// Write a message to the server
	void Write(const Message& msg) {
		std::cout << ":: Sending to thread " << m_thread.get_id() << std::endl;

		m_io_service.post(boost::bind(&ClientNetworkImpl::Send, this, msg));
	}

	// Close the connection
	void Close() {
		m_io_service.post(boost::bind(&ClientNetworkImpl::_Close, this));
	}

	// Getter for the thread
	boost::shared_ptr<boost::thread> thread() {
		return boost::shared_ptr<boost::thread>(&m_thread);
	}

private:

	// Handle an incoming connection
	void OnConnect(const boost::system::error_code& error) {
		if (!error) {
			std::cout << "Connected" << std::endl;
			ReadHeader();
		}
	}

	// Handle a incoming header
	void OnHeader(const boost::system::error_code& error) {
		std::cout << "Recieving a message" << std::endl;

		// Decode the header
		if (!error && m_read_msg.decode_header()) {
			ReadBody();
		} else {
			_Close();
		}
	}

	// Handle a incoming body message
	void OnBody(const boost::system::error_code& error) {
		std::cout << "Reading the message" << std::endl;
		if (!error) {
			// TODO: Handle the message
			// std:cout << read_msg_.body() << std::endl;
			std::cout.write(m_read_msg.body(), m_read_msg.body_length());
			std::cout << "\n";
			// Go back to read header
			ReadHeader();
		} else {
			_Close();
		}
	}

	// Read header and call [...], when done
	void ReadHeader() {
		boost::asio::async_read(m_socket,
				boost::asio::buffer(m_read_msg.data(), Message::header_length),
				boost::bind(&ClientNetworkImpl::OnHeader, this,
						boost::asio::placeholders::error));
	}

	// Read the body and call [...], when done
	void ReadBody() {
		boost::asio::async_read(m_socket,
				boost::asio::buffer(m_read_msg.body(), m_read_msg.body_length()),
				boost::bind(&ClientNetworkImpl::OnBody, this,
						boost::asio::placeholders::error));
	}

	// Send a message to the server
	void Send(Message msg) {
		std::cout << ":::: Now in WriteMessage" << std::endl;
		bool write_in_progress = !m_write_msgs.empty();
		m_write_msgs.push_back(msg);

		// If not already writing: Write message and call HandleWrite
		_Write();
	}

	// Process a written message: Remove it from the queue and proceed to the next one
	void OnWrite(const boost::system::error_code& error) {
		std::cout << ":::: Now in HandleWrite" << std::endl;

		if (!error) {
			m_write_msgs.pop_front();
			_Write();
		} else {
			_Close();
		}
	}

private:
	// Process the next waiting message and call HandleWrite, when done
	void _Write() {
		std::cout << ":::: Now in _Write" << std::endl;

		if (!m_write_msgs.empty()) {
			Message msg = m_write_msgs.front();

			boost::asio::async_write(m_socket,
					boost::asio::buffer(msg.data(), msg.length()),
					boost::bind(&ClientNetworkImpl::OnWrite, this,
							boost::asio::placeholders::error));
		}
	}

	// Do any cleanup stuff and close the connection
	void _Close() {
		m_socket.close();
	}

	boost::thread m_thread;

	boost::asio::io_service m_io_service;
	tcp::socket m_socket;

	tcp::resolver m_tcp_resolver;
	tcp::resolver::query m_tcp_query;
	tcp::resolver::iterator m_tcp_endpoint_iterator;

	Message m_read_msg; // The last message being read
	MessageQueue m_write_msgs; // A queue for running write operations
};

int main(int argc, char* argv[]) {
	try {
		if (argc != 3) {
			std::cerr << "Usage: chat_client <host> <port>\n";
			return 1;
		}

		std::cout << ":: Initializing the client..." << std::endl;
		ClientNetworkImpl c(argv[1], argv[2]);

		char line[Message::max_body_length + 1];

		std::cout << ":: Now in read loop..." << std::endl;

		while (std::cin.getline(line, Message::max_body_length + 1)) {
			std::cout << ":: Got input" << std::endl;

			Message msg((const char*) line);
			msg.encode_header();
			c.Write(msg);
		}

		c.Close();
		c.thread()->join();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
