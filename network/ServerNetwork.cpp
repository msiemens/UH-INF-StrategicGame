/*
 * ServerNetwork.cpp
 *
 *  Created on: 26.11.2012
 *      Author: markus
 */

#include <sstream>
#include <iostream>
#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include "messages/message_types.h"
#include "network/ServerNetwork.h"

ServerNetwork::ServerNetwork(int port) :
		m_network(port) {
	std::cout << "ServerNetwork::ServerNetwork(" << port << ")" << std::endl;
	// Connect OnPlayerConnect to be run when new players connect
	m_network.ConnectOnPlayerConnect(
			boost::bind(&ServerNetwork::OnPlayerConnect, this, _1));
	m_network.ConnectOnMessage(
			boost::bind(&ServerNetwork::OnMessage, this, _1, _2));
}

ServerNetwork::~ServerNetwork() {
}

boost::shared_ptr<boost::thread> ServerNetwork::thread() {
	return m_network.thread();
}

void ServerNetwork::OnPlayerConnect(NetPlayerPtr netplayer) {
	std::cout << "ServerNetwork::OnPlayerConnect(...)" << std::endl;
	std::cout << "Creating PlayerPtr" << std::endl;
	PlayerPtr player(new Player);
	std::cout << "Inserting player" << std::endl;
	try {
		// m_players[player] = netplayer;
	} catch (std::bad_alloc &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "Exiting ServerNetwork::OnPlayerConnect(...)" << std::endl;
}

void ServerNetwork::SendAction(PlayerPtr dest, GameActionPtr action) {
	std::stringstream buffer;

	// Initialize Serialization
	boost::archive::text_oarchive oa(buffer);

	// Serialize object
	buffer << message_types::action;
	buffer << action;

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
	buffer << action;

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

void ServerNetwork::OnMessage(char* message, int length) {
	std::cout << "OnMessage!" << std::endl;

	std::stringstream buffer;

	std::cout << "Writing message to buffer: " << string(message, length) << "  (" << length << ")" << std::endl;
	// Write message object to buffer
	buffer.write(message, length);

	std::cout << "Message we got: " << buffer.str() << std::endl;

	std::cout << "Initializing deserialization" << std::endl;
	// Initialize Deserialization
	boost::archive::text_iarchive archive(buffer);

	std::cout << "Reading message type" << std::endl;
	// Read message type
	message_types message_type;
	archive >> message_type;

	switch (message_type) {
	case message_types::action:
		GameActionPtr* action;
		archive >> action;
		std::cout << "Got an action!" << std::endl;
		// TODO: Call Server OnPlayerAction
		break;
	case message_types::metamessage:
		GameMetaMessagePtr* message;
		std::cout << "Got an metamessage!" << std::endl;
		// archive >> message;
		// TODO: Call Server OnMetaMessage
		break;
	default:
		break;
	}

	std::cout << buffer.str() << std::endl;
}
