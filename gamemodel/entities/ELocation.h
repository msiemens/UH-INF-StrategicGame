/*
 * EPlace.h
 *
 *  Created on: 23.11.2012
 *      Author: Henrik
 */

#ifndef EPLACE_H_
#define EPLACE_H_

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/uuid/uuid.hpp>

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

	boost::uuids::uuid GetOwner();
	void SetOwner(boost::uuids::uuid id);
	bool owned;

public:
	EArmyPtr town_army;

private:
	boost::uuids::uuid owner;
	std::vector<EBuildingPtr> m_buildings;
	int m_inhabitans;
	coordinates assemblypoint;

	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameEntity>(*this);

		ar & m_buildings;
		ar & m_inhabitans;
		ar & assemblypoint;
	}
};

typedef boost::shared_ptr<ELocation> ELocationPtr;

#endif /* EPLACE_H_ */
