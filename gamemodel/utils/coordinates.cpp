/*
 * coordinates.cpp
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#include "coordinates.h"

coordinates::coordinates() :
		x(0),
		y(0) {

}

coordinates::coordinates(int x, int y) :
		x(x),
		y(y) {

}

coordinates::~coordinates() {

}

std::ostream& operator <<(std::ostream& out, const coordinates& coords) {
	out << "[" << coords.x << ";" << coords.y << "]";
	return out;
}
