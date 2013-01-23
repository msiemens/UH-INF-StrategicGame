/*
 * ECavalry.h
 *
 *  Created on: 15.01.2013
 *      Author: Henrik
 */

#ifndef ECAVALRY_H_
#define ECAVALRY_H_

#include <gamemodel/entities/EUnit.h>

class ECavalry: public EUnit {
public:
	ECavalry();
	virtual ~ECavalry();


private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<EUnit>(*this);
	}
};

typedef boost::shared_ptr<ECavalry> ECavalryPtr;

#endif /* ECAVALRY_H_ */
