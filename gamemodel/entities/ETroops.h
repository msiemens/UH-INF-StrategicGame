/*
 * ETroops.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef ETROOPS_H_
#define ETROOPS_H_

#include <boost/shared_ptr.hpp>

#include <gamemodel/GameEntity.h>
#include <string>

class ETroops: public GameEntity {
public:
	ETroops();
	virtual ~ETroops();

	int EXP;

	//Attributes
	int ATK,DEF,PAC,MOR,TAC;
	int amount;


};

typedef boost::shared_ptr<ETroops> ETroopsPtr;

#endif /* ETROOPS_H_ */
