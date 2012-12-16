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
#include <network/messages/GameMetaMessage.h>

#include "server/ServerNetworkImpl.h"

using namespace std;

class ServerNetwork {
public:
	ServerNetwork(int port);
	virtual ~ServerNetwork();

	boost::shared_ptr<boost::thread> thread();

	void SendAction(PlayerPtr dest, GameActionPtr action);
	void BroadcastAction(GameActionPtr action);

	void SendMessage(PlayerPtr dest, GameStateMessagePtr message);
	void BroadcastMessage(GameStateMessagePtr message);

private:
	void OnPlayerConnect(NetPlayerPtr netplayer);
	void OnMessage(char* message, int length);

	ServerNetworkImpl m_network;

	std::unordered_map<PlayerPtr, NetPlayerPtr> m_players;
};

#endif /* SERVERNETWORK_H_ */
