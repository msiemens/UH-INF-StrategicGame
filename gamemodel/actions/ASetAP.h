/*
 * ASetAP.h
 *
 *  Created on: 11.01.2013
 *      Author: Meholli
 */

#ifndef ASETAP_H_
#define ASETAP_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <gamemodel/utils/coordinates.h>

using namespace std;

class ASetAP {
public:
	ASetAP();
	virtual ~ASetAP();

	coordinates basecoords;
	coordinates apcoords;
private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameAction>(*this);

		ar & basecoords;
		ar & apcoords;
	}
};

typedef boost::shared_ptr<ASetAP> ASetAPPtr;

#endif /* ASETAP_H_ */
