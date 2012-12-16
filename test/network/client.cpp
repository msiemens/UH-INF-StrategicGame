/*
 * client.cpp
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#include <iostream>

#include <gamemodel/GameRessource.h>
#include <gamemodel/GameEntity.h>
#include <network/ClientNetwork.h>

int main(int argc, char* argv[]) {
	try {
		if (argc != 3) {
			std::cerr << "Usage: chat_client <host> <port>\n";
			return 1;
		}

		std::cout << ":: Initializing the client..." << std::endl;
		ClientNetwork c(argv[1], atoi(argv[2]));

		GameActionPtr action(new GameAction);

		GameRessource res;
		res.count = 200;
		counter<GameRessource> price(200);

		GameEntity entity;
		coordinates coords(5, 5);
		entity.coords = coords;
		entity.cost = price;

		action->what = entity;

		c.SendAction(action);

		c.thread()->join();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	} catch (boost::system::error_code& e) {
		std::cerr << "Exception " << e.value() << ": " << e.message() << "\n";
	}

	return 0;
}
