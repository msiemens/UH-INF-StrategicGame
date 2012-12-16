/*
 * ServerNetwork.cpp
 *
 *  Created on: 26.11.2012
 *      Author: markus
 */

#include <sstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "messages/message_types.h"
#include "network/ServerNetwork.h"

ServerNetwork::ServerNetwork(int port): m_network(port) {
	// Connect OnPlayerConnect to be run when new players connect
	m_network.ConnectOnPlayerConnect(
			boost::bind(&ServerNetwork::OnPlayerConnect, this, _1));
}

ServerNetwork::~ServerNetwork() {
}

void ServerNetwork::OnPlayerConnect(NetPlayerPtr netplayer) {
	PlayerPtr player(new Player);
	m_players.insert(std::make_pair(player, netplayer));
}

void ServerNetwork::SendAction(PlayerPtr dest, GameActionPtr action) {
	std::stringstream buffer;

	// Initialize Serialization
	boost::archive::text_oarchive oa(buffer);

	// Serialize object
	buffer << message_types::action;
	// buffer << action;

	// Create NetworkMessage
	NetworkMessagePtr msg(new NetworkMessage(buffer.str().c_str()));

	// Pass message to m_network.send
	m_players.at(dest)->Send(msg);
}

void ServerNetwork::SendMessage(PlayerPtr dest, GameStateMessagePtr message) {
	std::stringstream buffer;

	// Initialize Serialization
	boost::archive::text_oarchive oa(buffer);

	// Serialize object
	buffer << message_types::statemessage;
	// buffer << message;

	// Create NetworkMessage
	NetworkMessagePtr msg(new NetworkMessage(buffer.str().c_str()));

	// Pass message to m_network.send
	m_players.at(dest)->Send(msg);
}

void ServerNetwork::BroadcastAction(GameActionPtr action) {
	std::stringstream buffer;

	// Initialize Serialization
	boost::archive::text_oarchive oa(buffer);

	// Serialize object
	buffer << message_types::action;
	// buffer << action;

	// Create NetworkMessage
	NetworkMessagePtr msg(new NetworkMessage(buffer.str().c_str()));

	// Pass message to m_network.send
	m_network.game()->Broadcast(msg);
}

void ServerNetwork::BroadcastMessage(GameStateMessagePtr message) {
	std::stringstream buffer;

	// Initialize Serialization
	boost::archive::text_oarchive oa(buffer);

	// Serialize object
	buffer << message_types::statemessage;
	// buffer << message;

	// Create NetworkMessage
	NetworkMessagePtr msg(new NetworkMessage(buffer.str().c_str()));

	// Pass message to m_network.send
	m_network.game()->Broadcast(msg);
}
