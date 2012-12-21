/*
 * Player.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <list>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/functional/hash.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "utils/counter.h"

#include "GameEntity.h"
#include "GameRessource.h"
#include "entities/EArmy.h"
#include "entities/EPlace.h"

class Player {
public:
	Player();
	virtual ~Player();

	boost::uuids::uuid getPlayerId();
	string getPlayerIdStr();

	void addArmy(EArmyPtr army);
	void addPlace(EPlacePtr place);
	void addTroops(ETroopsPtr troops);

	void addRessource(GameRessourcePtr ressource);

	int getRessourceCount(GameRessourcePtr ressource);

	void setImgPath(string path);
	string getImgPath();
	string imgpath;

	boost::uuids::uuid id;

	std::list<counter<GameEntityPtr> > owns;
	std::list<counter<GameRessourcePtr> > has;

	std::list<EArmyPtr> armies;
	std::list<EPlacePtr> places;
};

typedef boost::shared_ptr<Player> PlayerPtr;

// Hasher for Player used in std::map/std::set etc.
namespace std {
template<>
class hash<Player> {
public:
	size_t operator()(const Player &p) const {
		boost::hash<boost::uuids::uuid> hasher;
		return hasher(p.id);
	}
};

template<>
class hash<PlayerPtr> {
public:
	size_t operator()(const PlayerPtr &p) const {
		return hash<Player>()(*p);
	}
};
}

#endif /* PLAYER_H_ */
