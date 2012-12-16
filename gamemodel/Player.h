/*
 * Player.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <list>

#include <boost/functional/hash.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <boost/shared_ptr.hpp>

#include "utils/counter.h"

#include "GameEntity.h"
#include "GameRessource.h"

class Player {
public:
	Player();
	virtual ~Player();

	std::list<counter<GameEntity> > owns;
	std::list<counter<GameRessource> > has;

	boost::uuids::uuid id;
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
		return hash<PlayerPtr>()(p);
	}
};
}

#endif /* PLAYER_H_ */
