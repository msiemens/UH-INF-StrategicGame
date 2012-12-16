/*
 * Player.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <list>
#include <boost/shared_ptr.hpp>
#include <string>

#include "utils/count.h"
#include "GameEntity.h"
#include "GameRessource.h"
#include "entities/EArmy.h"
#include "entities/EPlace.h"

class Player {
public:
	Player(int id);
	virtual ~Player();

	int getPlayerId();
	void addArmy(EArmyPtr army);
	void addPlace(EPlacePtr place);
	void addTroops(ETroopsPtr troops);

	void addRessource(GameRessourcePtr ressource);

	int getRessourceCount(GameRessourcePtr ressource);

	int playerId;

	std::list<counter<GameEntityPtr> > owns;
	std::list<counter<GameRessourcePtr> > has;

	std::list<EArmyPtr> armies;
	std::list<EPlacePtr> places;
};

typedef boost::shared_ptr<Player> PlayerPtr;

#endif /* PLAYER_H_ */
