/*
 * NetworkMessage.h
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#ifndef NETWORKMESSAGE_H_
#define NETWORKMESSAGE_H_

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

class NetworkMessage {
public:
	enum {
		header_length = 8
	};
	enum {
		max_body_length = 1024
	};

	NetworkMessage();

	NetworkMessage(const char* body_);

	const char* data() const;

	char* data();

	size_t length() const;

	const char* body() const;

	char* body();

	size_t body_length() const;

	void body_length(size_t new_length);

	bool DecodeHeader();

	void EncodeHeader();

private:
	char m_data[header_length + max_body_length];
	size_t m_body_length;
};
#endif /* NETWORKMESSAGE_H_ */
