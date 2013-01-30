/*
 * SMEndGame.h
 *
 *  Created on: 30.01.2013
 *      Author: Meholli
 */

#ifndef SMENDGAME_H_
#define SMENDGAME_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <network/messages/GameStateMessage.h>

class SMEndGame: public GameStateMessage {
public:
	virtual ~SMEndGame();
	bool win;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameStateMessage>(*this);
		ar & win;
	}
};

typedef boost::shared_ptr<SMEndGame> SMEndGamePtr;
#endif /* SMENDGAME_H_ */
