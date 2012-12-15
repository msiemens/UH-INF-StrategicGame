/*
 * EArmy.h
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#ifndef EARMY_H_
#define EARMY_H_

#include "gamemodel/GameEntity.h"
#include "gamemodel/utils/coordinates.h"
#include "gamemodel/entities/ETroops.h"
#include <list>
#include <vector>

namespace std {

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

	void addTroop(ETroops troop);

private:
	vector<ETroops> troops;

	int atk, def, pac, mor, tac;
};

} /* namespace std */
#endif /* EARMY_H_ */
