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
#include "gamemodel/entities/EUnit.h"
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
	int getSteps();

	void setAtk();
	void setDef();
	void setPac(int x);
	void setMor();
	void setTac();
	void setStep(int x);

	void Move(int dir, int size);
	void addTroop(EUnitPtr troop);

	std::vector<EUnitPtr> units;
private:
	int atk, def, pac, mor, tac, steps;
};

typedef boost::shared_ptr<EArmy> EArmyPtr;

#endif /* EARMY_H_ */
