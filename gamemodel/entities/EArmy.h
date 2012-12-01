/*
 * EArmy.h
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#ifndef EARMY_H_
#define EARMY_H_

#include <GameEntity.h>
#include <gamemodel/utils/coordinates.h>
#include "gamemodel/entities/ATroops.h"
#include <list>

namespace std {

class EArmy: public GameEntity {
public:
	EArmy();
	virtual ~EArmy();

	coordinates position;

	void setPosition(int x,int y);

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

	void addTroop(ETroops troop,int slot);

private:
	ETroops troops[];

	int atk,def,pac,mor,tac;
};

} /* namespace std */
#endif /* EARMY_H_ */
