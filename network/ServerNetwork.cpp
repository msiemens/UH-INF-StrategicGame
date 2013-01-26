/*
 * ServerNetwork.cpp
 *
 *  Created on: 26.11.2012
 *      Author: markus
 */

#include <sstream>
#include <iostream>
#include <string>

#include <boost/serialization/shared_ptr.hpp>

#include <gamemodel/utils/coordinates.h>
#include <gamemodel/utils/counter.h>
#include <gamemodel/entities/EArmy.h>
#include <gamemodel/entities/ELocation.h>
#include <gamemodel/entities/EUnit.h>
#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/AAttack.h>
#include <gamemodel/actions/ABuild.h>
#include <gamemodel/actions/AMove.h>
#include <gamemodel/actions/ASetAP.h>
#include <gamemodel/actions/ASetTurn.h>
#include <gamemodel/actions/ALogIn.h>
#include <gamemodel/entities/units/ECavalry.h>
#include <gamemodel/entities/units/EInfantry.h>
#include <gamemodel/entities/units/EPawn.h>

#include "messages/message_types.h"
#include "messages/metamessages/MMTest.h"
#include "messages/statemessages/SMUpdateRessources.h"
#include "messages/statemessages/SMUpdateUUID.h"
#include "messages/statemessages/SMSetStartBase.h"
#include "messages/statemessages/SMUpdateActionsLeft.h"
#include "messages/statemessages/SMBattleResult.h"
#include "messages/statemessages/SMSetLocationOwner.h"

#include "messages/statemessages/SMTest.h"

#include "ServerNetwork.h"

ServerNetwork::ServerNetwork(int port) :
		m_network(port) {
	std::cout << "ServerNetwork::ServerNetwork(" << port << ")" << std::endl;
	// Connect OnPlayerConnect to be run when new players connect
	m_network.ConnectOnPlayerConnect(
			boost::bind(&ServerNetwork::OnPlayerConnect, this, _1));
	m_network.ConnectOnMessage(
			boost::bind(&ServerNetwork::OnMessage, this, _1, _2, _3));
}

ServerNetwork::~ServerNetwork() {
}

boost::shared_ptr<boost::thread> ServerNetwork::thread() {
	return m_network.thread();
}

void ServerNetwork::ConnectOnAction(
		const signal_action_t::slot_type &subscriber) {
	m_signal_on_action.connect(subscriber);
}

void ServerNetwork::ConnectOnMessage(
		const signal_meta_t::slot_type &subscriber) {
	m_signal_on_message.connect(subscriber);
}

void ServerNetwork::ConnectOnPlayerConnect(
		const signal_connect_t::slot_type &subscriber) {
	m_signal_on_connect.connect(subscriber);
}

void ServerNetwork::OnPlayerConnect(NetPlayerPtr netplayer) {
	PlayerPtr player(new Player);
	m_players[player] = netplayer;

	// Call onConnect handler
	m_signal_on_connect(player);
}

void ServerNetwork::SendAction(PlayerPtr dest, GameActionPtr action) {
	std::stringstream buffer;

	// Initialize Serialization
	boost::archive::text_oarchive archive(buffer);
	registerTypes(&archive);

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
	std::cout << "Sending Message" << std::endl;

	std::stringstream buffer;

	// Initialize Serialization
	boost::archive::text_oarchive archive(buffer);
	registerTypes(&archive);

	// Serialize object
	int type = MESSAGE_STATE;
	archive << type;
	archive << message;

	// Create NetworkMessage
	NetworkMessagePtr msg(new NetworkMessage(buffer.str().c_str()));

	// Pass message to m_network.send
	m_players.at(dest)->Send(msg);
}

void ServerNetwork::BroadcastAction(GameActionPtr action) {
	std::cout << "Broadcasting Action" << std::endl;

	std::stringstream buffer;

	// Initialize Serialization
	boost::archive::text_oarchive archive(buffer);
	registerTypes(&archive);

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
	registerTypes(&archive);

	// Serialize object
	int type = MESSAGE_STATE;
	archive << type;
	archive << message;

	// Create NetworkMessage
	NetworkMessagePtr msg(new NetworkMessage(buffer.str().c_str()));

	// Pass message to m_network.send
	m_network.game()->Broadcast(msg);
}

void ServerNetwork::OnMessage(char* message, int length, NetPlayerPtr netplayer) {
	PlayerPtr player;

	for (auto pair : m_players) {
		if (pair.second == netplayer) {
			player = pair.first;
		}
	}

	std::stringstream buffer;

	// Write message object to buffer
	buffer.write(message, length);

	// Initialize Deserialization
	boost::archive::text_iarchive archive(buffer);
	registerTypes(&archive);

	// Read message type
	int message_type;
	archive >> message_type;

	switch (message_type) {
	case MESSAGE_ACTION: {
		std::cout << "Got an action" << std::endl;
		GameActionPtr action(new GameAction);
		archive >> action;

		m_signal_on_action(action, player);
		break;
	}
	case MESSAGE_META: {
		std::cout << "Got an metamessage" << std::endl;
		GameMetaMessagePtr message(new GameMetaMessage);
		archive >> message;

		m_signal_on_message(message, player);
		break;
	}
	default:
		break;
	}
}

void ServerNetwork::registerTypes(boost::archive::text_oarchive* archive) {
	archive->register_type<ALogIn>();
	archive->register_type<ARecruit>();
	archive->register_type<ABuild>();
	archive->register_type<AMove>();
	archive->register_type<AAttack>();
	archive->register_type<ASetAP>();
	archive->register_type<ASetTurn>();

	archive->register_type<EArmy>();
	archive->register_type<ELocation>();
	archive->register_type<EUnit>();
	archive->register_type<EPawn>();
	archive->register_type<ECavalry>();
	archive->register_type<EInfantry>();

	archive->register_type<coordinates>();
	archive->register_type<ASetAP>();
	archive->register_type<ASetTurn>();
	archive->register_type<counter<GameRessource> >();

	archive->register_type<MMTest>();
	archive->register_type<SMUpdateRessources>();
	archive->register_type<SMUpdateUUID>();
	archive->register_type<SMSetStartBase>();
	archive->register_type<SMUpdateActionsLeft>();
	archive->register_type<SMBattleResult>();
	archive->register_type<SMSetLocationOwner>();

	archive->register_type<SMTest>();
}

void ServerNetwork::registerTypes(boost::archive::text_iarchive* archive) {
	archive->register_type<ALogIn>();
	archive->register_type<ARecruit>();
	archive->register_type<ABuild>();
	archive->register_type<AMove>();
	archive->register_type<AAttack>();
	archive->register_type<ASetAP>();
	archive->register_type<ASetTurn>();

	archive->register_type<EArmy>();
	archive->register_type<ELocation>();
	archive->register_type<EUnit>();
	archive->register_type<EPawn>();
	archive->register_type<ECavalry>();
	archive->register_type<EInfantry>();

	archive->register_type<coordinates>();
	archive->register_type<ASetAP>();
	archive->register_type<ASetTurn>();
	archive->register_type<counter<GameRessource> >();

	archive->register_type<MMTest>();
	archive->register_type<SMUpdateRessources>();
	archive->register_type<SMUpdateUUID>();
	archive->register_type<SMSetStartBase>();
	archive->register_type<SMUpdateActionsLeft>();
	archive->register_type<SMBattleResult>();
	archive->register_type<SMSetLocationOwner>();

	archive->register_type<SMTest>();
}
