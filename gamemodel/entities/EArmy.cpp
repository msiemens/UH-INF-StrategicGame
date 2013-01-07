/*
 * EArmy.cpp
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#include "EArmy.h"

EArmy::EArmy() {
}

EArmy::~EArmy() {
}

void EArmy::addTroop(EUnitPtr unit) {
	m_units.push_back(unit);
}
