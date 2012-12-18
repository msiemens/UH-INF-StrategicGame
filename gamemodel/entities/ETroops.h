/*
 * ETroops.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef ETROOPS_H_
#define ETROOPS_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>

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

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & EXP;
		ar & ATK;
		ar & DEF;
		ar & PAC;
		ar & MOR;
		ar & TAC;
		ar & amount;
	}

};

typedef boost::shared_ptr<ETroops> ETroopsPtr;

#endif /* ETROOPS_H_ */
