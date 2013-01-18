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
#include "entities/EUnit.h"
#include "entities/ELocation.h"

class Player {
public:
	Player();
	virtual ~Player();

	boost::uuids::uuid getPlayerId();
	std::string getPlayerIdStr();

	void addArmy(EArmyPtr army);
	void addLocation(ELocationPtr place);
	void addUnit(EUnitPtr unit);
/*
	template<class T_VALUE>
	void addRessource() {
		// Find existing counter
		for (auto c : has) {
			if (c.GetType() == typeid(T_VALUE)) {
				c.how_many++;
				return;
			}
		}
		// Not found, insert it
		has.insert(counter<T_VALUE>());
	}


	template<class T_VALUE>
	int getRessourceCount() {
		for (auto c : has) {
			if (c.GetType() == typeid(T_VALUE)) {
				return c.how_many;
			}
		}
	}

	int getRessourceCount(GameRessourcePtr ressource);
	void addRessource(int count) {
		// Find existing counter
		for (auto c : has) {
			if (c.GetType() == typeid(T_VALUE)) {
				c.how_many += count;
				return;
			}
		}
		// Not found, insert it
		has.insert(counter<T_VALUE>(count));
	}

	void addRessource(GameRessource res) {
		// Find existing counter
		for (auto c : has) {
			if (c.GetType() == typeid(res)) {
				c.how_many++;
				return;
			}
		}
		// Not found, insert it
		has.insert(counter<res>());
	}

	template<class T_VALUE>
	void addRessource(int count) {
		// Find existing counter
		for (auto c : has) {
			if (c.GetType() == typeid(T_VALUE)) {
				c.how_many += count;
				return;
			}
		}
		// Not found, insert it
		has.insert(counter<T_VALUE>(count));
	}

	template<class T_VALUE>
*/
	int actionsleft;
	int GetActionLeft();
	void SetActionLeft(int x);
	void setImgPath(string path);
	string getImgPath();
	string imgpath;
	bool onturn;

	boost::uuids::uuid id;

	std::list<counter<GameEntityPtr> > owns;
	std::list<counter<GameRessourcePtr> > has;

	std::list<EArmyPtr> armies;
	std::list<ELocationPtr> places;
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
