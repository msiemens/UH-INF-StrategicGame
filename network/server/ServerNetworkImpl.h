/*
 * ServerNetworkImpl.h
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#ifndef SERVERNETWORKIMPL_H_
#define SERVERNETWORKIMPL_H_

#include <deque>
#include <unordered_map>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/signals2.hpp>

#include <gamemodel/Player.h>

#include "../NetworkMessage.h"
#include "NetConnection.h"
#include "NetGame.h"
#include "NetPlayer.h"

using boost::asio::ip::tcp;
using namespace std;

class ServerNetworkImpl {
public:
	typedef boost::signals2::signal<void(NetPlayerPtr)> signal_t;

	ServerNetworkImpl(int port);

	NetGamePtr game();

	// Connect to onPlayerConnect signal
	void ConnectOnPlayerConnect(const signal_t::slot_type &handler);

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

	signal_t m_signal_on_player_connect;

};

#endif /* SERVERNETWORKIMPL_H_ */
