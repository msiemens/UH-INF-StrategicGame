/*
 * NetPlayer.h
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#ifndef NETPLAYER_H_
#define NETPLAYER_H_

#include <deque>

#include <boost/asio.hpp>
#include <boost/signals2.hpp>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "../NetworkMessage.h"
#include "NetConnection.h"
#include "NetGame.h"

using boost::asio::ip::tcp;
using namespace std;

typedef std::deque<NetworkMessagePtr> MessageQueue;

class NetPlayer: public NetConnection, public boost::enable_shared_from_this<
		NetPlayer> {
public:
	typedef boost::signals2::signal<void(char*, int)> signal_t;

	NetPlayer(boost::asio::io_service& io_service, NetGame& game);

	void ConnectOnMessage(const signal_t::slot_type &handler);

	tcp::socket& socket();

	// Start listening on our socket
	void Start();

	// Send a message to a player
	void Send(NetworkMessagePtr msg);

	// Handle an incoming header
	void OnHeader(const boost::system::error_code& error);

	// Handle incoming body
	void OnBody(const boost::system::error_code& error);

	// OnWriteHandler
	void OnWrite(const boost::system::error_code& error);

private:
	tcp::socket m_socket;
	NetGame& m_game;
	NetworkMessagePtr m_read_msg;
	MessageQueue m_write_msgs;

	signal_t m_signal_on_message;

	void _Write(NetworkMessagePtr msg);

	void _ReadHeader();

	void _ReadBody();
};

typedef boost::shared_ptr<NetPlayer> NetPlayerPtr;
#endif /* NETPLAYER_H_ */
