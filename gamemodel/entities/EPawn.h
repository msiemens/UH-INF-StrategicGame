/*
 * EPawn.h
 *
 *  Created on: 20.11.2012
 *      Author: Armend
 */

#ifndef EPAWN_H_
#define EPAWN_H_

#include <gamemodel/entities/ETroops.h>
#include <string>

class EPawn: public ETroops {
public:
	EPawn();
	int GET_att(int i);
	int GET_cost();
	int GET_amount();
	std::string GET_name();
	virtual ~EPawn();
};

#endif /* EPAWN_H_ */
