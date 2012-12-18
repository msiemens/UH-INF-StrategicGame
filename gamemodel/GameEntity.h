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
#include <boost/shared_ptr.hpp>

#include "utils/counter.h"
#include "utils/coordinates.h"
#include "GameRessource.h"
#include <string>
using namespace std;

class GameEntity {
public:
	GameEntity();

	counter<GameRessource> cost;

	coordinates getCoords();

	void setCoords(int x, int y);
	void setCoords(coordinates coords);

	std::string getName();
	void setName(std::string name);

	void setImgPath(string path);
	string getImgPath();
protected:
	std::string name;

private:
	coordinates coords;
	string imgpath;

	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & cost;
		ar & coords;
	}
};

typedef boost::shared_ptr<GameEntity> GameEntityPtr;

#endif /* GAMEENTITY_H_ */
