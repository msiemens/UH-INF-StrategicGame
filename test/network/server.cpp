/*
 * server.cpp
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#include <network/server/ServerNetworkImpl.h>


int main(int argc, char* argv[]) {
	try {
		if (argc < 2) {
			std::cerr << "Usage: " << argv[0] << " <port> [<port> ...]\n";
			return 1;
		}

		new ServerNetworkImpl(atoi(argv[1]));

	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
