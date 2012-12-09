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

namespace std {

class EArmy: public GameEntity {
public:
	EArmy();
	virtual ~EArmy();

	coordinates position;

	void setPosition(int x, int y);
	void setPosition(coordinates coords);

	coordinates getPosition();

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

	void addTroop(ETroops troop, int slot);

private:
	// ETroops troops[]; // Nimm bitte lieber "vector". Ist deutlich einfacher und sicherer von der Handhabung.
	// Hier kannst du aus versehen in falsche Speicherbereiche reinschreiben und dann Happy Debugging.
	//

	int atk, def, pac, mor, tac;
};

} /* namespace std */
#endif /* EARMY_H_ */
