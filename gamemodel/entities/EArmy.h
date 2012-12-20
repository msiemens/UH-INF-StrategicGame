/*
 * EArmy.h
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#ifndef EARMY_H_
#define EARMY_H_

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <gamemodel/GameEntity.h>
#include <gamemodel/utils/coordinates.h>
#include <gamemodel/entities/EUnit.h>

class EArmy: public GameEntity {
public:
	EArmy();
	virtual ~EArmy();

	void addTroop(EUnitPtr unit);

private:
	std::vector<EUnitPtr> m_units;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameEntity>(*this);
	}
};

typedef boost::shared_ptr<EArmy> EArmyPtr;

#endif /* EARMY_H_ */
