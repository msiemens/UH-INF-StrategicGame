/*
 * insertplayer.cpp
 *
 *  Created on: 21.12.2012
 *      Author: markus
 */

	#include <unordered_map>

	#include <network/server/NetPlayer.h>
	#include <gamemodel/Player.h>


	int main(int argc, char **argv) {
		NetGame game;
		boost::asio::io_service io_service;

		NetPlayerPtr net(new NetPlayer(io_service, game));
		PlayerPtr player(new Player);

		std::unordered_map<PlayerPtr, NetPlayerPtr> player_map;

		player_map[player] = net;
	}
