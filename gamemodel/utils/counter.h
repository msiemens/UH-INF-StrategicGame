/*
 * count.h
 *
 *  Created on: 07.11.2012
 *      Author: markus
 */

#ifndef COUNT_H_
#define COUNT_H_

#include <typeinfo>

#include <boost/serialization/access.hpp>

template<class T_VALUE>
class counter {
public:
	counter() :
			how_many(0) {
	}
	counter(int count) :
			how_many(count) {
	}

	std::type_info GetType() {
		return typeid(T_VALUE);
	}


public:
	int how_many;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & how_many;
	}
};

#endif /* COUNT_H_ */
