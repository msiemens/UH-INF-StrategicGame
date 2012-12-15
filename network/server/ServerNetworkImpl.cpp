/*
 * ServerNetworkImpl.cpp
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#include "ServerNetworkImpl.h"

ServerNetworkImpl::ServerNetworkImpl(int port) :
		m_io_service(), m_endpoint(tcp::v4(), port), m_acceptor(m_io_service,
				m_endpoint) {
	// Start accepting connections
	StartAccept();

	// Run the IO service
	m_io_service.run();
}

NetGamePtr ServerNetworkImpl::game() {
	return NetGamePtr(&m_room);
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
		player->Start();
	}

	// Listen for more connections
	StartAccept();
}
