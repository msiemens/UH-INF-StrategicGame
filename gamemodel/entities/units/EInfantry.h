/*
 * EInfantry.h
 *
 *  Created on: 15.01.2013
 *      Author: Henrik
 */

#ifndef EINFANTRY_H_
#define EINFANTRY_H_

#include <gamemodel/entities/EUnit.h>

class EInfantry: public EUnit {
public:
	EInfantry();
	virtual ~EInfantry();

};

typedef boost::shared_ptr<EInfantry> EInfantryPtr;
#endif /* EINFANTRY_H_ */
