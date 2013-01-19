/*
 * GameContainer.h
 *
 *  Created on: 17.01.2013
 *      Author: Henrik
 */

#ifndef GAMECONTAINER_H_
#define GAMECONTAINER_H_

#include <boost/bind.hpp>

#include <list>
#include <vector>
#include <gamemodel/Player.h>
#include <gamemodel/entities/ELocation.h>
#include <gamemodel/entities/EArmy.h>
#include <gamemodel/entities/EUnit.h>

class GameContainer {
public:
	GameContainer();
	virtual ~GameContainer();

	vector<PlayerPtr> playerlist;
	vector<ELocationPtr> locationlist;
	vector<EArmyPtr> armylist;
	vector<EUnitPtr> unitlist;

	void addUnit(EUnitPtr unit);
	void removeUnit(EUnitPtr unit);

	void addArmy(EArmyPtr army);
	void removeArmy(EArmyPtr army);

	void addLocation(ELocationPtr location);
	void removeLocation(ELocationPtr location);

	void addPlayer(PlayerPtr player);
	void removePlayer(PlayerPtr player);

	EArmyPtr getArmy(int index);
	EUnitPtr getUnit(int index);
	ELocationPtr getLocation(int index);
	PlayerPtr getPlayer(int index);

	PlayerPtr getPlayerById(boost::uuids::uuid playerId);
	vector<EUnitPtr> *getUnitVectorPtrByArmy(EArmyPtr army);


	int getPlayerCount();
	int getArmyCount();
	int getUnitCount();
	int getLocationCount();

	vector<EArmyPtr> *getArmyListPtr();
	vector<ELocationPtr> *getLocationListPtr();
	vector<PlayerPtr> *getPlayerListPtr();
	vector<EUnitPtr> *getUnitListPtr();


};

#endif /* GAMECONTAINER_H_ */
