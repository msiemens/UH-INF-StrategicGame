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
#include <unordered_map>

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

	void setPlayerId(boost::uuids::uuid new_id);
	boost::uuids::uuid getPlayerId();
	std::string getPlayerIdStr();

	void addArmy(EArmyPtr army);
	void addLocation(ELocationPtr place);
	void addUnit(EUnitPtr unit);

	void addRessource(GameRessource res, int count);
	template<class T_VALUE>
	void addRessource(int count) {
		has[typeid(T_VALUE).name()] += count;
	}

	int getRessourceCount(GameRessource res);
	template<class T_VALUE>
	int getRessourceCount() {
		return has[typeid(T_VALUE).name()];
	}
private:
	int wood;
	int gold;
	int stone;

public:
	void setGold(int value);
	void setWood(int value);
	void setStone(int value);
	int getGold();
	int getWood();
	int getStone();

	int actionsleft;
	int GetActionLeft();
	void SetActionLeft(int x);
	void setImgPath(string path);
	string getImgPath();
	string imgpath;
	bool onturn;

	boost::uuids::uuid id;

	std::list<counter<GameEntityPtr> > owns;
	std::unordered_map<const char*, int> has;

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
