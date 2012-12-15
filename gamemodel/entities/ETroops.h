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

	int EXP;
	//int cost;

	//Attributes
	int ATK,DEF,PAC,MOR,TAC;
	int amount;


};

#endif /* ETROOPS_H_ */
