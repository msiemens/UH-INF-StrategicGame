/*
 * AAttack.h
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#ifndef AATTACK_H_
#define AATTACK_H_

#include <boost/shared_ptr.hpp>

#include <gamemodel/utils/coordinates.h>

#include <gamemodel/GameAction.h>

class AAttack: public GameAction {
public:
	virtual ~AAttack();

	coordinates where;
};

typedef boost::shared_ptr<AAttack> AAttackPtr;

#endif /* AATTACK_H_ */
