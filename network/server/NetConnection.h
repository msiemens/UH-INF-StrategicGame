/*
 * NetConnection.h
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#ifndef NETCONNECTION_H_
#define NETCONNECTION_H_

#include <boost/shared_ptr.hpp>

class NetworkMessage;

class NetConnection {
public:
	virtual ~NetConnection() {
	}
	virtual void Send(const NetworkMessage& msg) = 0;
};

typedef boost::shared_ptr<NetConnection> NetClientPtr;

#endif /* NETCONNECTION_H_ */
