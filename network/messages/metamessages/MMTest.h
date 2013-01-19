/*
 * ETroops.h
 *
 *  Created on: 19.01.2013
 *      Author: markus
 */

#ifndef MMTEST_H_
#define MMTEST_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <network/messages/GameMetaMessage.h>

class MMTest: public GameMetaMessage {
public:
    MMTest();
    virtual ~MMTest();

    int test;

private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<GameMetaMessage>(*this);
        ar & test;
    }
};

typedef boost::shared_ptr<MMTest> MMTestPtr;

#endif /* MMTEST_H_ */