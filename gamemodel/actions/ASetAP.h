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

namespace std {

class ASetAP {
public:
	ASetAP();
	virtual ~ASetAP();

	coordinates basecoords;
	int ap_x;
	int ap_y;
private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameAction>(*this);

		ar & basecoords;
		ar & ap_x;
		ar & ap_y;
	}
};

} /* namespace std */
#endif /* ASETAP_H_ */
