/*
 * GameAction.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef GAMEACTION_H_
#define GAMEACTION_H_

#include <boost/shared_ptr.hpp>

#include "GameEntity.h"
#include "GameRessource.h"

class GameAction {
public:
	GameAction();
	virtual ~GameAction();

	GameEntityPtr what;
	GameRessourcePtr costs;
};

typedef boost::shared_ptr<GameAction> GameActionPtr;

#endif /* GAMEACTION_H_ */
