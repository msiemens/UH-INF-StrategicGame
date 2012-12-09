/*
 * NetworkMessage.cpp
 *
 *  Created on: 09.12.2012
 *      Author: markus
 */

#include "network/NetworkMessage.h"

NetworkMessage::NetworkMessage() :
		m_body_length(0) {
}

NetworkMessage::NetworkMessage(const char* body_) {
	body_length(strlen(body_));
	memcpy(body(), body_, body_length());
}

const char* NetworkMessage::data() const {
	return m_data;
}

char* NetworkMessage::data() {
	return m_data;
}

size_t NetworkMessage::length() const {
	return header_length + m_body_length;
}

const char* NetworkMessage::body() const {
	return m_data + header_length;
}

char* NetworkMessage::body() {
	return m_data + header_length;
}

size_t NetworkMessage::body_length() const {
	return m_body_length;
}

void NetworkMessage::body_length(size_t new_length) {
	m_body_length = new_length;
	if (m_body_length > max_body_length)
		m_body_length = max_body_length;
}

bool NetworkMessage::DecodeHeader() {
	using namespace std;
	// For strncat and atoi.
	char header[header_length + 1] = "";
	strncat(header, m_data, header_length);
	m_body_length = atoi(header);
	if (m_body_length > max_body_length) {
		m_body_length = 0;
		return false;
	}

	return true;
}

void NetworkMessage::EncodeHeader() {
	using namespace std;
	// For sprintf and memcpy.
	char header[header_length + 1] = "";
	sprintf(header, "%4d", m_body_length);
	memcpy(m_data, header, header_length);
}
