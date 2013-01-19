/*
 * ETroops.h
 *
 *  Created on: 19.01.2013
 *      Author: markus
 */

#ifndef SMTEST_H_
#define SMTEST_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <network/messages/GameStateMessage.h>

class SMTest: public GameStateMessage {
public:
    SMTest();
    virtual ~SMTest();

    int test;

private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<GameStateMessage>(*this);
        ar & test;
    }
};

typedef boost::shared_ptr<SMTest> SMTestPtr;

#endif /* SMTEST_H_ */