/*
 * GameRessource.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef GAMERESSOURCE_H_
#define GAMERESSOURCE_H_

#include <boost/serialization/access.hpp>

class GameRessource {
public:
	GameRessource();
	virtual ~GameRessource();

	int count;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & count;
	}
};

#endif /* GAMERESSOURCE_H_ */
