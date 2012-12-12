/*
 * client.cpp
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#include <iostream>

#include <network/client/ClientNetworkImpl.h>

using namespace std;

int main(int argc, char* argv[]) {
	try {
		if (argc != 3) {
			std::cerr << "Usage: chat_client <host> <port>\n";
			return 1;
		}

		std::cout << ":: Initializing the client..." << std::endl;
		ClientNetworkImpl c(argv[1], argv[2]);

		char line[NetworkMessage::max_body_length + 1];

		std::cout << ":: Now in read loop..." << std::endl;

		while (std::cin.getline(line, NetworkMessage::max_body_length + 1)) {
			std::cout << ":: Got input" << std::endl;

			NetworkMessage msg((const char*) line);
			msg.EncodeHeader();
			c.Write(msg);
		}

		c.Close();
		c.thread()->join();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	} catch (boost::system::error_code& e) {
		std::cerr << "Exception " << e.value() << ": " << e.message() << "\n";
	}

	return 0;
}
