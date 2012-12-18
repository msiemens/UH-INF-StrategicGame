/*
 * ClientNetworkImpl.h
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#ifndef CLIENTNETWORKIMPL_H_
#define CLIENTNETWORKIMPL_H_

#include <deque>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/signals2.hpp>

#include "../NetworkMessage.h"

using boost::asio::ip::tcp;

typedef std::deque<NetworkMessagePtr> MessageQueue;

class ClientNetworkImpl {
public:
	typedef boost::signals2::signal<void(char*, int)> signal_t;

	ClientNetworkImpl(const char* host, const char* port);

	// Write a message to the server
	void Write(NetworkMessagePtr msg);

	// Close the connection
	void Close();

	// Signals connectors
	void ConnectOnMessage(const signal_t::slot_type &subscriber);

	// Getter for the thread
	boost::shared_ptr<boost::thread> thread();

private:

	// Handle an incoming connection
	void OnConnect(const boost::system::error_code& error);

	// Handle a incoming header
	void OnHeader(const boost::system::error_code& error);

	// Handle a incoming body message
	void OnBody(const boost::system::error_code& error);

	// Read header and call [...], when done
	void ReadHeader();

	// Read the body and call [...], when done
	void ReadBody();

	// Send a message to the server
	void Send(NetworkMessagePtr msg);

	// Process a written message: Remove it from the queue and proceed to the next one
	void OnWrite(const boost::system::error_code& error);

	// Process the next waiting message and call HandleWrite, when done
	void _Write();

	// Do any cleanup stuff and close the connection
	void _Close();

	//
	void OnConnectionTimeout(const boost::system::error_code& error);

private:

	boost::thread m_thread;

	boost::asio::io_service m_io_service;
	tcp::socket m_socket;
	boost::asio::deadline_timer m_timer;

	tcp::resolver m_tcp_resolver;
	tcp::resolver::query m_tcp_query;
	tcp::resolver::iterator m_tcp_endpoint_iterator;

	NetworkMessage m_read_msg; // The last message being read
	MessageQueue m_write_msgs; // A queue for running write operations

	signal_t m_signal_on_message;
};

#endif /* CLIENTNETWORKIMPL_H_ */
