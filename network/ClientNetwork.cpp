/*
 * ClientNetwork.cpp
 *
 *  Created on: 22.11.2012
 *      Author: markus
 */

#include <sstream>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include "messages/message_types.h"
#include "messages/GameStateMessage.h"

#include "ClientNetwork.h"

ClientNetwork::ClientNetwork(string hostname, int port) :
		m_network(hostname.c_str(), boost::lexical_cast<string>(port).c_str()) {
	// Connect OnMessage to recieve messages
	m_network.ConnectOnMessage(
			boost::bind(&ClientNetwork::OnMessage, this, _1, _2));
}

ClientNetwork::~ClientNetwork() {
}

void ClientNetwork::SendAction(GameActionPtr action) {
	std::stringstream buffer;
	boost::archive::text_oarchive archive(buffer);

	// Serialize object
	buffer << message_types::action;
	// buffer << action;

	// Create NetworkMessage
	NetworkMessagePtr msg(new NetworkMessage(buffer.str().c_str()));

	// Pass message to m_network.send
	m_network.Write(msg);
}

void ClientNetwork::SendMetaMessage(GameMetaMessagePtr message) {
	std::stringstream buffer;
	boost::archive::text_oarchive archive(buffer);

	// Serialize object
	buffer << message_types::metamessage;
	// buffer << message;

	// Create NetworkMessage
	NetworkMessagePtr msg(new NetworkMessage(buffer.str().c_str()));

	// Pass message to m_network.send
	m_network.Write(msg);
}

void ClientNetwork::OnMessage(char* msg, int length) {
	std::stringstream buffer;

	// Write message object to buffer
	buffer.write(msg, length);

	// Initialize Deserialization
	boost::archive::text_iarchive archive(buffer);

	// Read message type
	message_types message_type;
	archive >> message_type;

	switch (message_type) {
	case message_types::action:
		GameActionPtr* action;
		// archive >> action;
		// TODO: Call Client OnPlayerAction
		break;
	case message_types::statemessage:
		GameStateMessagePtr* message;
		// archive >> message;
		// TODO: Call Client OnStateMessage
		break;
	default:
		break;
	}

	std::cout << buffer.str() << std::endl;
}
