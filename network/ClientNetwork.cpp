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

#include <gamemodel/utils/coordinates.h>
#include <gamemodel/utils/counter.h>
#include <gamemodel/entities/EArmy.h>
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
#include "messages/metamessages/MMTest.h"
#include "messages/statemessages/SMUpdateRessources.h"
#include "messages/statemessages/SMUpdateUUID.h"
#include "messages/statemessages/SMSetStartBase.h"
#include "messages/statemessages/SMUpdateActionsLeft.h"
#include "messages/statemessages/SMBattleResult.h"
#include "messages/statemessages/SMSetLocationOwner.h"
#include "messages/statemessages/SMUpdateArmy.h"
#include "messages/statemessages/SMRemoveArmy.h"
#include "messages/statemessages/SMUpdateLocationArmy.h"
#include "messages/statemessages/SMEndGame.h"

#include "messages/statemessages/SMTest.h"


#include "messages/message_types.h"
#include "ClientNetwork.h"

using namespace std;

ClientNetwork::ClientNetwork(string hostname, int port) :
		m_network(hostname.c_str(), boost::lexical_cast<string>(port).c_str()) {
	// Connect OnMessage to recieve messages
	m_network.ConnectOnMessage(
			boost::bind(&ClientNetwork::OnMessage, this, _1, _2));
}

ClientNetwork::ClientNetwork(char* hostname, char* port) :
		m_network(hostname, port) {
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
	std::cout << "Sending action" << std::endl;

	std::stringstream buffer;

	boost::archive::text_oarchive archive(buffer);
	registerTypes(&archive);

	// Serialize object
	int type = MESSAGE_ACTION;
	archive << type;
	archive << action;

	// Create NetworkMessage
	NetworkMessagePtr msg(new NetworkMessage(buffer.str().c_str()));

	// Pass message to m_network.send
	m_network.Write(msg);
}

void ClientNetwork::SendMetaMessage(GameMetaMessagePtr message) {
	std::cout << "Sending metamessage" << std::endl;

	std::stringstream buffer;

	boost::archive::text_oarchive archive(buffer);
	registerTypes(&archive);

	// Serialize object
	int type = MESSAGE_META;
	archive << type;
	archive << message;

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
	registerTypes(&archive);

	// Read message type
	int message_type;
	archive >> message_type;

	switch (message_type) {
		case MESSAGE_ACTION: {
			std::cout << "Got an action" << std::endl;
			GameActionPtr action(new GameAction);
			archive >> action;

			m_signal_on_action(action);
			break;
		}
		case MESSAGE_STATE: {
			std::cout << "Got an statemessage" << std::endl;
			GameStateMessagePtr message(new GameStateMessage);
			archive >> message;

			m_signal_on_message(message);
			break;
		}
	default:
		break;
	}
}

void ClientNetwork::registerTypes(boost::archive::text_oarchive* archive) {
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
	archive->register_type<SMUpdateArmy>();
	archive->register_type<SMRemoveArmy>();
	archive->register_type<SMUpdateLocationArmy>();
	archive->register_type<SMEndGame>();

	archive->register_type<SMTest>();
}

void ClientNetwork::registerTypes(boost::archive::text_iarchive* archive) {
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
	archive->register_type<SMUpdateArmy>();
	archive->register_type<SMRemoveArmy>();
	archive->register_type<SMUpdateLocationArmy>();
	archive->register_type<SMEndGame>();

	archive->register_type<SMTest>();
}
