/*
 * ALogIn.h
 *
 *  Created on: 14.01.2013
 *      Author: Meholli
 */

#ifndef ALOGIN_H_
#define ALOGIN_H_

#include <iostream>

#include <gamemodel/GameAction.h>

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
//#include <boost/uuid/uuid.hpp>

using namespace std;

class ALogIn: public GameAction{
public:
	virtual ~ALogIn();

	//boost::uuids::uuid id;
	bool verified;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameAction>(*this);
		//ar & id;
		ar & verified;

	}
};

typedef boost::shared_ptr<ALogIn> ALogInPtr;
#endif /* ALOGIN_H_ */
