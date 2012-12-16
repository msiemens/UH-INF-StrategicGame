/*

 * GameEntity.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef GAMEENTITY_H_
#define GAMEENTITY_H_

#include <boost/shared_ptr.hpp>

#include "utils/count.h"
#include "utils/coordinates.h"
#include "GameRessource.h"

#include <string>

class GameEntity {
public:
	GameEntity(); // abstract class
	virtual ~GameEntity();

	counter<GameRessource> cost;

	coordinates getCoords();

	void setCoords(int x, int y);
	void setCoords(coordinates coords);

	std::string getName();
	void setName(std::string name);

private:
	coordinates coords;

protected:
	std::string name;
};

typedef boost::shared_ptr<GameEntity> GameEntityPtr;

#endif /* GAMEENTITY_H_ */
