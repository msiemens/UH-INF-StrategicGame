/*
 * ASetTurn.h
 *
 *  Created on: 12.01.2013
 *      Author: Meholli
 */

#ifndef ASETTURN_H_
#define ASETTURN_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <gamemodel/GameAction.h>

class ASetTurn: public GameAction {
public:
	virtual ~ASetTurn();

 	 bool endturn;//false=onturn, true = endturn;
private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameAction>(*this);
		ar & endturn;
	}
};
typedef boost::shared_ptr<ASetTurn> ASetTurnPtr;

#endif /* ASETTURN_H_ */
