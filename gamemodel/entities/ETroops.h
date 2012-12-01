/*
 * ETroops.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef ETROOPS_H_
#define ETROOPS_H_

#include <gamemodel/GameEntity.h>
#include <string>

class ETroops: public GameEntity {
public:
	ETroops();
	virtual ~ETroops();

	std::string name;
	int EXP;
	int cost;

	//Attributes
	int MOR;
	int ATK;
	int DEF;
	int PAC;
	int TAC;

	int amount;


};

#endif /* ETROOPS_H_ */
