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

#include <gamemodel/actions/ARecruit.h>
#include "messages/message_types.h"

#include "ClientNetwork.h"

using namespace std;

ClientNetwork::ClientNetwork(string hostname, int port) :
		m_network(hostname.c_str(), boost::lexical_cast<string>(port).c_str()) {
	// Connect OnMessage to recieve messages
	m_network.ConnectOnMessage(
			boost::bind(&ClientNetwork::OnMessage, this, _1, _2));
}

ClientNetwork::~ClientNetwork() {
}

boost::shared_ptr<boost::thread> ClientNetwork::thread() {
	return m_network.thread();
}

void ClientNetwork::ConnectOnAction(const signal_action_t::slot_type &subscriber) {
	m_signal_on_action.connect(subscriber);
}

void ClientNetwork::ConnectOnMessage(const signal_state_t::slot_type &subscriber) {
	m_signal_on_message.connect(subscriber);
}

void ClientNetwork::SendAction(GameActionPtr action) {
	std::stringstream buffer;

	std::cout << "Doing Initialization of Serialization" << std::endl;
	boost::archive::text_oarchive archive(buffer);

	archive.register_type<ARecruit>();

	// Serialize object
	int type = MESSAGE_ACTION;
	std::cout << "Serializing MessageType" << std::endl;
	archive << type;
	std::cout << "Serializing GameAction" << std::endl;
	archive << action;

	// Create NetworkMessage
	std::cout << "Creating NetworkMessage" << std::endl;
	NetworkMessagePtr msg(new NetworkMessage(buffer.str().c_str()));

	// Pass message to m_network.send
	std::cout << "Sending Message" << std::endl;
	m_network.Write(msg);
}

void ClientNetwork::SendMetaMessage(GameMetaMessagePtr message) {
	std::stringstream buffer;
	boost::archive::text_oarchive archive(buffer);

	// Serialize object
	int type = MESSAGE_META;
	archive << type;
	// archive << message;

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
	int message_type;
	archive >> message_type;

	switch (message_type) {
		case MESSAGE_ACTION: {
			std::cout << "Got an action!" << std::endl;
			GameActionPtr action(new GameAction);
			archive >> action;

			m_signal_on_action(action);
			break;
		}
		case MESSAGE_STATE: {
			std::cout << "Got an metamessage!" << std::endl;
			GameStateMessagePtr message(new GameStateMessage);
			// archive >> message;

			m_signal_on_message(message);
			break;
		}
	default:
		break;
	}

	std::cout << buffer.str() << std::endl;
}
