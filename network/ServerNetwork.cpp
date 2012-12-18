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

#include <gamemodel/actions/ARecruit.h>
#include "messages/message_types.h"
#include "ServerNetwork.h"

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

void ServerNetwork::ConnectOnAction(const signal_action_t::slot_type &subscriber) {
	m_signal_on_action.connect(subscriber);
}

void ServerNetwork::ConnectOnMessage(const signal_meta_t::slot_type &subscriber) {
	m_signal_on_message.connect(subscriber);
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
	boost::archive::text_oarchive archive(buffer);
	archive.register_type<ARecruit>();

	// Serialize object
	int type = MESSAGE_ACTION;
	archive << type;
	archive << action;

	// Create NetworkMessage
	NetworkMessagePtr msg(new NetworkMessage(buffer.str().c_str()));

	// Pass message to m_network.send
	m_players.at(dest)->Send(msg);
}

void ServerNetwork::SendMessage(PlayerPtr dest, GameStateMessagePtr message) {
	std::stringstream buffer;

	// Initialize Serialization
	boost::archive::text_oarchive archive(buffer);
	archive.register_type<ARecruit>();

	// Serialize object
	int type = MESSAGE_STATE;
	archive << type;
	// archive << message;

	// Create NetworkMessage
	NetworkMessagePtr msg(new NetworkMessage(buffer.str().c_str()));

	// Pass message to m_network.send
	m_players.at(dest)->Send(msg);
}

void ServerNetwork::BroadcastAction(GameActionPtr action) {
	std::stringstream buffer;

	// Initialize Serialization
	boost::archive::text_oarchive archive(buffer);
	archive.register_type<ARecruit>();

	// Serialize object
	int type = MESSAGE_ACTION;
	archive << type;
	archive << action;

	// Create NetworkMessage
	NetworkMessagePtr msg(new NetworkMessage(buffer.str().c_str()));

	// Pass message to m_network.send
	m_network.game()->Broadcast(msg);
}

void ServerNetwork::BroadcastMessage(GameStateMessagePtr message) {
	std::stringstream buffer;

	// Initialize Serialization
	boost::archive::text_oarchive archive(buffer);

	// Serialize object
	int type = MESSAGE_STATE;
	archive << type;
	// archive << message;

	// Create NetworkMessage
	NetworkMessagePtr msg(new NetworkMessage(buffer.str().c_str()));

	// Pass message to m_network.send
	m_network.game()->Broadcast(msg);
}

void ServerNetwork::OnMessage(char* message, int length) {
	std::stringstream buffer;

	// Write message object to buffer
	buffer.write(message, length);

	// Initialize Deserialization
	boost::archive::text_iarchive archive(buffer);
	archive.register_type<ARecruit>();

	// Read message type
	int message_type;
	archive >> message_type;

	switch (message_type) {
	case MESSAGE_ACTION: {
		std::cout << "Got an action!" << std::endl;
		GameActionPtr action(new GameAction);
		archive >> action;

		std::cout << "Deserialization done!" << std::endl;

		m_signal_on_action(action);
		break;
	}
	case MESSAGE_META: {
		std::cout << "Got an metamessage!" << std::endl;
		GameMetaMessagePtr message(new GameMetaMessage);
		// archive >> message;

		m_signal_on_message(message);
		break;
	}
	default:
		break;
	}
}
