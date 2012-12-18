/*
 * GameAction.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef GAMEACTION_H_
#define GAMEACTION_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>

#include "GameEntity.h"
#include "GameRessource.h"

class GameAction {
public:
	GameAction();
	virtual ~GameAction();

	GameEntityPtr what;
	GameRessourcePtr costs;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & what;
	}
};

typedef boost::shared_ptr<GameAction> GameActionPtr;

#endif /* GAMEACTION_H_ */
