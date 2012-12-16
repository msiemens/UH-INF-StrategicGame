/*
 * GameEntity.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef GAMEENTITY_H_
#define GAMEENTITY_H_

#include "utils/count.h"
#include "utils/coordinates.h"
#include "GameRessource.h"

class GameEntity {
public:
	GameEntity(); // abstract class
	virtual ~GameEntity();

	count<GameRessource> cost;
	coordinates coords;
};

#endif /* GAMEENTITY_H_ */
