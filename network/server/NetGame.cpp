/*
 * NetGame.cpp
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include "NetConnection.h"

#include "NetGame.h"

void NetGame::Join(NetClientPtr participant) {
	m_players.insert(participant);
}

void NetGame::Leave(NetClientPtr participant) {
	m_players.erase(participant);
}

void NetGame::Broadcast(NetworkMessagePtr msg) {
	std::for_each(m_players.begin(), m_players.end(),
			boost::bind(&NetConnection::Send, _1, boost::ref(msg)));
}

