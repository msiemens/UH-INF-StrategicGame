/*
 * SMBattleResult.h
 *
 *  Created on: 21.01.2013
 *      Author: Meholli
 */

#ifndef SMBATTLERESULT_H_
#define SMBATTLERESULT_H_

#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <network/messages/GameStateMessage.h>
#include <gamemodel/entities/EArmy.h>
#include <gamemodel/utils/coordinates.h>

class SMBattleResult: public GameStateMessage {
public:
	virtual ~SMBattleResult();
	EArmyPtr winner;
	coordinates looser_coords;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {

		std::cout << "Serializing BattleResult" << std::endl;

		ar & boost::serialization::base_object<GameStateMessage>(*this);
		ar & winner;
		ar & looser_coords;
	}
};

typedef boost::shared_ptr<SMBattleResult> SMBattleResultPtr;
#endif /* SMBATTLERESULT_H_ */
