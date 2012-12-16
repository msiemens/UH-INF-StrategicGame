/*
 * server.cpp
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#include <network/ServerNetwork.h>


int main(int argc, char* argv[]) {
	try {
		if (argc < 2) {
			std::cerr << "Usage: " << argv[0] << " <port>\n";
			return 1;
		}

		ServerNetwork net(atoi(argv[1]));
		net.thread()->join();

	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
