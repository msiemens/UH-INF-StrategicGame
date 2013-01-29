/*
 * ClientNetwork.h
 *
 *  Created on: 22.11.2012
 *      Author: markus
 */

#ifndef CLIENTNETWORK_H_
#define CLIENTNETWORK_H_

#include <string>

#include <boost/thread.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <gamemodel/GameAction.h>
#include <network/messages/GameMetaMessage.h>
#include <network/messages/GameStateMessage.h>

#include "client/ClientNetworkImpl.h"

using namespace std;

class ClientNetwork {
public:
	typedef boost::signals2::signal<void(GameActionPtr)> signal_action_t;
	typedef boost::signals2::signal<void(GameStateMessagePtr)> signal_state_t;

	ClientNetwork(string hostname, int port);
	ClientNetwork(char* hostname, char* port);
	virtual ~ClientNetwork();

	void ConnectOnAction(const signal_action_t::slot_type &subscriber);
	void ConnectOnMessage(const signal_state_t::slot_type &subscriber);

	void SendAction(GameActionPtr action);
	void SendMetaMessage(GameMetaMessagePtr message);

	boost::shared_ptr<boost::thread> thread();
private:
	ClientNetworkImpl m_network;

	signal_action_t m_signal_on_action;
	signal_state_t m_signal_on_message;

	void OnMessage(char* msg, int length);
	void registerTypes(boost::archive::text_iarchive* archive);
	void registerTypes(boost::archive::text_oarchive* archive);
};

#endif /* CLIENTNETWORK_H_ */
