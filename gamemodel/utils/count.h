/*
 * count.h
 *
 *  Created on: 07.11.2012
 *      Author: markus
 */

#ifndef COUNT_H_
#define COUNT_H_

template<class T_VALUE>
class counter {
public:
	counter(int count): how_many(count) {

	}

	virtual ~counter() {

	}

	int how_many;

	typedef T_VALUE type;
};

#endif /* COUNT_H_ */
