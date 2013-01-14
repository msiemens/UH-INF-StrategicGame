/*

 * GameEntity.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef GAMEENTITY_H_
#define GAMEENTITY_H_

#include <string>


#include <boost/serialization/access.hpp>

#include <boost/uuid/uuid_serialize.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <boost/shared_ptr.hpp>

#include "utils/counter.h"
#include "utils/coordinates.h"

using namespace std;
class GameRessource;

class GameEntity {
public:
	GameEntity();

	coordinates getCoords();

	void setCoords(int x, int y);
	void setCoords(coordinates coords);


	boost::uuids::uuid GetOwner();
	void SetOwner(boost::uuids::uuid id);

public:
	counter<GameRessource> cost;

	void setImgPath(string path);
	string getImgPath();
	void setIconPath(string path);
	string getIconPath();
protected:
	std::string name;

private:
	boost::uuids::uuid owner;
	coordinates coords;
	string imgpath;
	string iconpath;

	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & cost;
		ar & coords;
		ar & owner;
	}
};

typedef boost::shared_ptr<GameEntity> GameEntityPtr;

#endif /* GAMEENTITY_H_ */
