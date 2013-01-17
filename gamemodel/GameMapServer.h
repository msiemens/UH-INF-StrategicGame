/*
 * GameMapServer.h
 *
 *  Created on: 17.01.2013
 *      Author: Henrik
 */

#ifndef GAMEMAPSERVER_H_
#define GAMEMAPSERVER_H_

#include <boost/bind.hpp>

#include <gamemodel/GameMap.h>
#include <gamemodel/Player.h>
#include <gamemodel/entities/ELocation.h>
#include <server/GameContainer.h>

class GameMapServer: public GameMap {
public:
	GameMapServer();
	GameMapServer(GameContainer *container);
	virtual ~GameMapServer();

	void createPlaces();
	void createArmyAt(coordinates coords, PlayerPtr player);

	ELocationPtr getPlaceAt(coordinates coords);
	EArmyPtr getArmyAt(coordinates coords);

	boost::uuids::uuid whoseLocationAt(coordinates coords);
	boost::uuids::uuid whoseArmyAt(coordinates coords);

private:
	GameContainer *container;


};

#endif /* GAMEMAPSERVER_H_ */
