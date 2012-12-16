/*
 * AMove.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef AMOVE_H_
#define AMOVE_H_

#include <boost/shared_ptr.hpp>

#include <gamemodel/utils/coordinates.h>
#include <gamemodel/GameEntity.h>

#include <gamemodel/GameAction.h>

class AMove: public GameAction {
public:
	AMove();
	virtual ~AMove();

	coordinates to;
	GameEntityPtr what;
	int count;
};

typedef boost::shared_ptr<AMove> AMovePtr;

#endif /* AMOVE_H_ */
