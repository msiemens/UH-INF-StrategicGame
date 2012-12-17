/*
 * GameRessource.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef GAMERESSOURCE_H_
#define GAMERESSOURCE_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>

class GameRessource {
public:
	GameRessource();
	virtual ~GameRessource();

	int getCount();

private:
	int count;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & count;
	}
};

typedef boost::shared_ptr<GameRessource> GameRessourcePtr;

#endif /* GAMERESSOURCE_H_ */
