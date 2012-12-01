/*
 * AAttack.h
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#ifndef AATTACK_H_
#define AATTACK_H_

#include <GameAction.h>
#include "gamemodel/entities/EPlace.h"
#include "gamemodel/utils/coordinates.h"

namespace std {

class AAttack: public GameAction {
public:
	AAttack();
	virtual ~AAttack();

	coordinates where;
};

} /* namespace std */
#endif /* AATTACK_H_ */
