/*
 * ClientNetwork.h
 *
 *  Created on: 22.11.2012
 *      Author: markus
 */

#ifndef CLIENTNETWORK_H_
#define CLIENTNETWORK_H_

#include <string>

#include <gamemodel/GameAction.h>
#include <network/messages/GameMetaMessage.h>

#include "client/ClientNetworkImpl.h"

using namespace std;

class ClientNetwork {
public:
	ClientNetwork(string hostname, int port);
	virtual ~ClientNetwork();

	void SendAction(GameActionPtr action);
	void SendMetaMessage(GameMetaMessagePtr message);

private:
	ClientNetworkImpl m_network;

	void OnMessage(char* msg, int length);
};

#endif /* CLIENTNETWORK_H_ */
