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
#include <GameNetwork.h>

using namespace std;

class ClientNetwork: public GameNetwork {
public:
	ClientNetwork();
	virtual ~ClientNetwork();

	void connectToServer(string hostname, int port);
	void sendAction(GameAction action);
	void sendMetaMessage(GameMetaMessage message);
};

#endif /* CLIENTNETWORK_H_ */
