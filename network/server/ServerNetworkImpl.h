/*
 * ServerNetworkImpl.h
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#ifndef SERVERNETWORKIMPL_H_
#define SERVERNETWORKIMPL_H_

#include <deque>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "../NetworkMessage.h"
#include "NetConnection.h"
#include "NetGame.h"
#include "NetPlayer.h"

using boost::asio::ip::tcp;
using namespace std;

typedef std::deque<NetworkMessage> MessageQueue;

class ServerNetworkImpl {
public:
	ServerNetworkImpl(int port);

	// Start accepting new connections
	void StartAccept();

	// Handle an incomming connection
	void HandleAccept(NetPlayerPtr session,
			const boost::system::error_code& error);

private:
	const tcp::endpoint m_endpoint;
	boost::asio::io_service m_io_service;
	tcp::acceptor m_acceptor;
	NetGame m_room;
};

#endif /* SERVERNETWORKIMPL_H_ */
