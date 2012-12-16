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

#include "GameEntity.h"
#include "GameRessource.h"

class Player {
public:
	Player();
	virtual ~Player();


	std::list<count<GameEntity> > owns;
	std::list<count<GameRessource> > has;

};

#endif /* PLAYER_H_ */
