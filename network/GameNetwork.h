/*
 * GameNetwork.h
 *
 *  Created on: 08.11.2012
 *      Author: markus
 */

#ifndef GAMENETWORK_H_
#define GAMENETWORK_H_

class GameNetwork {
public:
	GameNetwork();
	virtual ~GameNetwork();

	void launchServer();
	void launchClient();

	void sendMessage();
	void broadcastMessage();
};

#endif /* GAMENETWORK_H_ */
