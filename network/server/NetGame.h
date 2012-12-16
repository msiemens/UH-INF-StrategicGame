/*
 * NetGame.h
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#ifndef NETGAME_H_
#define NETGAME_H_

#include <set>

#include <boost/shared_ptr.hpp>

#include "../NetworkMessage.h"

class NetConnection;
typedef boost::shared_ptr<NetConnection> NetClientPtr;

class NetGame {
public:
	// Let a client join a game
	void Join(NetClientPtr participant);

	// Let a client leave
	void Leave(NetClientPtr participant);

	// Broadcast a message to all clients
	void Broadcast(NetworkMessagePtr msg);

private:
	std::set<NetClientPtr> m_players;
};

typedef boost::shared_ptr<NetGame> NetGamePtr;

#endif /* NETGAME_H_ */
