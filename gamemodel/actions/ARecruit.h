/*
 * ARecruit.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef ARECRUIT_H_
#define ARECRUIT_H_

#include <gamemodel/entities/ETroops.h>
#include <gamemodel/entities/EBuilding.h>

#include <gamemodel/GameAction.h>

class ARecruit: public GameAction {
public:
	ARecruit();
	virtual ~ARecruit();

	ETroops what;
	EBuilding base;
};

#endif /* ARECRUIT_H_ */
