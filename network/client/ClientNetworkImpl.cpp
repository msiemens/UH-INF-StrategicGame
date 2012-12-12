/*
 * ClientNetworkImpl.cpp
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#include <iostream>

#include "../constants.h"

#include "ClientNetworkImpl.h"

ClientNetworkImpl::ClientNetworkImpl(char* host, char* port) :
		m_io_service(),
		m_socket(m_io_service),
		m_tcp_resolver(m_io_service),
		m_tcp_query(host, port),
		m_tcp_endpoint_iterator(m_tcp_resolver.resolve(m_tcp_query)),
		m_timer(m_io_service) {

	// After init, listen for new connections and run handle_connect
	boost::asio::async_connect(m_socket, m_tcp_endpoint_iterator,
			boost::bind(&ClientNetworkImpl::OnConnect, this,
					boost::asio::placeholders::error));

	// Start the IO thread
	m_thread = boost::thread(
			boost::bind(&boost::asio::io_service::run, &m_io_service));

	// Start connection timeout timer
	m_timer.expires_from_now(boost::posix_time::seconds(kConnectionTimeout));
	m_timer.async_wait(boost::bind(&ClientNetworkImpl::OnConnectionTimeout, this,
			boost::asio::placeholders::error));
}

// Write a message to the server
void ClientNetworkImpl::Write(const NetworkMessage& msg) {
	m_io_service.post(boost::bind(&ClientNetworkImpl::Send, this, msg));
}

// Close the connection
void ClientNetworkImpl::Close() {
	m_io_service.post(boost::bind(&ClientNetworkImpl::_Close, this));
}

// Getter for the thread
boost::shared_ptr<boost::thread> ClientNetworkImpl::thread() {
	return boost::shared_ptr<boost::thread>(&m_thread);
}

// Handle an incoming connection
void ClientNetworkImpl::OnConnect(const boost::system::error_code& error) {
	if (!error) {
		m_timer.cancel(); // Cancel connection timeout timer
		std::cout << ":: Connected!" << std::endl;
		ReadHeader();
	}
}

// Handle a incoming header
void ClientNetworkImpl::OnHeader(const boost::system::error_code& error) {
	std::cout << "// Recieving a message" << std::endl;

// Decode the header
	if (!error && m_read_msg.DecodeHeader()) {
		ReadBody();
	} else {
		_Close();
		throw error;
	}
}

// Handle a incoming body message
void ClientNetworkImpl::OnBody(const boost::system::error_code& error) {
	std::cout << "// Reading the message" << std::endl;
	if (!error) {
		// TODO: Handle the message
		std::cout.write(m_read_msg.body(), m_read_msg.body_length());
		std::cout << "\n";

		// Go back to read header
		ReadHeader();
	} else {
		_Close();
		throw error;
	}
}

// Read header and call [...], when done
void ClientNetworkImpl::ReadHeader() {
	boost::asio::async_read(m_socket,
			boost::asio::buffer(m_read_msg.data(),
					NetworkMessage::header_length),
			boost::bind(&ClientNetworkImpl::OnHeader, this,
					boost::asio::placeholders::error));
}

// Read the body and call [...], when done
void ClientNetworkImpl::ReadBody() {
	boost::asio::async_read(m_socket,
			boost::asio::buffer(m_read_msg.body(), m_read_msg.body_length()),
			boost::bind(&ClientNetworkImpl::OnBody, this,
					boost::asio::placeholders::error));
}

// Send a message to the server
void ClientNetworkImpl::Send(NetworkMessage msg) {
	std::cout << ":::: Sending message" << std::endl;
	bool write_in_progress = !m_write_msgs.empty();
	m_write_msgs.push_back(msg);

// If not already writing: Write message and call HandleWrite
	_Write();
}

// Process a written message: Remove it from the queue and proceed to the next one
void ClientNetworkImpl::OnWrite(const boost::system::error_code& error) {
	if (!error) {
		m_write_msgs.pop_front();
		_Write();
	} else {
		_Close();
		throw error;
	}
}

// Process a connection timeout
void ClientNetworkImpl::OnConnectionTimeout(
		const boost::system::error_code& error) {
	if (error != boost::asio::error::operation_aborted) {
		_Close();
		throw "Connection timed out";
	}
}

// Process the next waiting message and call HandleWrite, when done
void ClientNetworkImpl::_Write() {
	if (!m_write_msgs.empty()) {
		NetworkMessage msg = m_write_msgs.front();

		boost::asio::async_write(m_socket,
				boost::asio::buffer(msg.data(), msg.length()),
				boost::bind(&ClientNetworkImpl::OnWrite, this,
						boost::asio::placeholders::error));
	}
}

// Do any cleanup stuff and close the connection
void ClientNetworkImpl::_Close() {
	m_socket.close();
}
