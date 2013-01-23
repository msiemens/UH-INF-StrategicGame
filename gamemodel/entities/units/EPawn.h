/*
 * EPawn.h
 *
 *  Created on: 15.01.2013
 *      Author: Henrik
 */

#ifndef EPAWN_H_
#define EPAWN_H_

#include <gamemodel/entities/EUnit.h>
class EPawn: public EUnit {
public:
	EPawn();
	virtual ~EPawn();


private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<EUnit>(*this);
	}
};
typedef boost::shared_ptr<EPawn> EPawnPtr;

#endif /* EPAWN_H_ */
