/*
 * ServerNetworkImpl.cpp
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#include <iostream>

#include "ServerNetworkImpl.h"

ServerNetworkImpl::ServerNetworkImpl(int port) :
		m_io_service(),
		m_endpoint(tcp::v4(), port),
		m_acceptor(m_io_service, m_endpoint) {
	// Start accepting connections
	StartAccept();

	// Start the IO thread
	m_thread = boost::thread(
			boost::bind(&boost::asio::io_service::run, &m_io_service));
}

NetGamePtr ServerNetworkImpl::game() {
	return NetGamePtr(&m_room);
}

// Getter for the thread
boost::shared_ptr<boost::thread> ServerNetworkImpl::thread() {
	return boost::shared_ptr<boost::thread>(&m_thread);
}

void ServerNetworkImpl::ConnectOnPlayerConnect(
		const signal_t::slot_type &handler) {
	m_signal_on_player_connect.connect(handler);
}

void ServerNetworkImpl::ConnectOnMessage(
		const NetPlayer::signal_t::slot_type &handler) {
	m_signals_on_message.push_back(handler);
}

// Start accepting new connections
void ServerNetworkImpl::StartAccept() {
	// Wait asynchronously for new connections
	NetPlayerPtr player(new NetPlayer(m_io_service, m_room));
	m_acceptor.async_accept(player->socket(),
			boost::bind(&ServerNetworkImpl::HandleAccept, this, player,
					boost::asio::placeholders::error));
}

// Handle an incomming connection
void ServerNetworkImpl::HandleAccept(NetPlayerPtr player,
		const boost::system::error_code& error) {
	if (!error) {
		// Connect all onMessage handlers to the current player
		for (auto handler : m_signals_on_message) {
			player->ConnectOnMessage(handler);
		}
		player->Start();
	}

	m_signal_on_player_connect(player);

	// Listen for more connections
	StartAccept();
}
