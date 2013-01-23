/*
 * EPlace.h
 *
 *  Created on: 23.11.2012
 *      Author: Henrik
 */

#ifndef EPLACE_H_
#define EPLACE_H_

#include <vector>
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>

#include <boost/uuid/uuid_serialize.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <gamemodel/GameEntity.h>
#include <gamemodel/entities/EArmy.h>
#include <gamemodel/entities/EBuilding.h>

class ELocation: public GameEntity {
public:
	ELocation();
	virtual ~ELocation();

	void addBuilding(EBuildingPtr building);
	coordinates GetAssemblyPointCoords();
	void SetAssemblyPointCoords(coordinates coords);
	void SetAssemblyPointCoord(int x, int y);
	void setStartBase(bool state);
	bool IsStartBase();

	bool owned;
public:
	EArmyPtr town_army;

private:
	std::vector<EBuildingPtr> m_buildings;
	int m_inhabitans;
	coordinates assemblypoint;
	bool isStartBase;

	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameEntity>(*this);
		ar & m_buildings;
		ar & m_inhabitans;
		ar & assemblypoint;
		ar & isStartBase;
		ar & owned;
	}
};

typedef boost::shared_ptr<ELocation> ELocationPtr;

#endif /* EPLACE_H_ */
