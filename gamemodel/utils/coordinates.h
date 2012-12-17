/*
 * coordinates.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef COORDINATES_H_
#define COORDINATES_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>

class coordinates {
public:
	coordinates();
	coordinates(int x, int y);
	virtual ~coordinates();

	int x;
	int y;
private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & x;
		ar & y;
	}
};

typedef boost::shared_ptr<coordinates> coordinatesPtr;

#endif /* COORDINATES_H_ */
