/*
 * coordinates.cpp
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#include "coordinates.h"

coordinates::coordinates(): x(0), y(0) {

}

// Such mal im Netz nach "c++ initialization list"
coordinates::coordinates(int x, int y): x(x), y(y) {

}


coordinates::~coordinates() {}
