/*
 * EArmy.h
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#ifndef EARMY_H_
#define EARMY_H_

#include <boost/shared_ptr.hpp>

#include "gamemodel/GameEntity.h"
#include "gamemodel/utils/coordinates.h"
#include "gamemodel/entities/ETroops.h"
#include <list>
#include <vector>

class EArmy: public GameEntity {
public:
	EArmy();
	virtual ~EArmy();


	int getAtk();
	int getDef();
	int getPac();
	int getMor();
	int getTac();

	void setAtk();
	void setDef();
	void setPac();
	void setMor();
	void setTac();

	void addTroop(ETroopsPtr troop);

private:
	std::vector<ETroopsPtr> troops;

	int atk, def, pac, mor, tac;
};

typedef boost::shared_ptr<EArmy> EArmyPtr;

#endif /* EARMY_H_ */
