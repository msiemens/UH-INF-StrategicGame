/*
 * count.h
 *
 *  Created on: 07.11.2012
 *      Author: markus
 */

#ifndef COUNT_H_
#define COUNT_H_

template<class T_VALUE>
class count {
public:
	count(int count);
	virtual ~count();

	int how_many;
};

#endif /* COUNT_H_ */
