//
// chat_message.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include <iostream>

using namespace std;

class Message {
public:
	enum {
		header_length = 8
	};
	enum {
		max_body_length = 1024
	};

	Message() :
			m_body_length(0) {
	}

	Message(const char* body_) {
		body_length(strlen(body_));
		memcpy(body(), body_, body_length());
	}

	const char* data() const {
		return m_data;
	}

	char* data() {
		return m_data;
	}

	size_t length() const {
		return header_length + m_body_length;
	}

	const char* body() const {
		return m_data + header_length;
	}

	char* body() {
		return m_data + header_length;
	}

	size_t body_length() const {
		return m_body_length;
	}

	void body_length(size_t new_length) {
		m_body_length = new_length;
		if (m_body_length > max_body_length)
			m_body_length = max_body_length;
	}

	bool decode_header() {
		using namespace std;
		// For strncat and atoi.
		char header[header_length + 1] = "";
		strncat(header, m_data, header_length);
		m_body_length = atoi(header);
		if (m_body_length > max_body_length) {
			m_body_length = 0;
			return false;
		}
		cout << "| Decoding message: " << m_data << " (" << m_body_length << ")"
				<< endl;

		return true;
	}

	void encode_header() {
		using namespace std;
		// For sprintf and memcpy.
		cout << "| Encoding message: " << m_data << " (" << m_body_length << ")"
				<< endl;
		char header[header_length + 1] = "";
		sprintf(header, "%4d", m_body_length);
		memcpy(m_data, header, header_length);
	}

private:
	char m_data[header_length + max_body_length];
	size_t m_body_length;
};

#endif // CHAT_MESSAGE_HPP
