/*
 * Player.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <list>

#include "utils/count.h"
#include <string>


#include "GameEntity.h"
#include "GameRessource.h"
#include "entities/EArmy.h"
#include "entities/EPlace.h"

class Player {
public:
	Player(int id);
	virtual ~Player();


	int getPlayerId();
	void addArmy(EArmy army);
	void addPlace(EPlace place);
	void addTroops(ETroops troops);

	void addRessource(GameRessource ressource);

	int getRessourceCount(GameRessource ressource);

	int playerId;



	std::list<count<GameEntity> > owns;
	std::list<count<GameRessource> > has;


	std::list<EArmy> armies;
	std::list<EPlace> places;
};

#endif /* PLAYER_H_ */
