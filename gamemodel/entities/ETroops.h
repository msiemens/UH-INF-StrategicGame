/*
 * ETroops.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef ETROOPS_H_
#define ETROOPS_H_

#include <gamemodel/GameEntity.h>

class ETroops: public GameEntity {
public:
	ETroops();
	virtual ~ETroops();

	int xp;
	int moral;
};

#endif /* ETROOPS_H_ */
