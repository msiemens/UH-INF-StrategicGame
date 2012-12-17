/*
 * ServerNetwork.h
 *
 *  Created on: 26.11.2012
 *      Author: markus
 */

#ifndef SERVERNETWORK_H_
#define SERVERNETWORK_H_

#include <gamemodel/Player.h>
#include <gamemodel/GameAction.h>
#include <network/messages/GameStateMessage.h>
#include <GameNetwork.h>

using namespace std;

class ServerNetwork: public GameNetwork {
public:
	ServerNetwork();
	virtual ~ServerNetwork();

	void startServer(int port);

	void sendAction(Player dest, GameAction action);
	void broadcastAction(GameAction action);

	void sendMessage(Player dest, GameStateMessage message);
	void broadcastMessage(GameStateMessage message);
};

#endif /* SERVERNETWORK_H_ */
