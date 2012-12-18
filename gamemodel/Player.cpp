/*
 * Player.cpp
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#include <iostream>
#include <sstream>

#include <boost/uuid/uuid_io.hpp>

#include "Player.h"

Player::Player() :
		id(boost::uuids::random_generator()()) {

}

Player::~Player() {

}

boost::uuids::uuid Player::getPlayerId() {
	return id;
}

string Player::getPlayerIdStr() {
	std::stringstream ss;
	ss << getPlayerId();
	return ss.str();
}

void Player::addArmy(EArmyPtr army) {
	armies.insert(armies.end(), army);
}

void Player::addPlace(EPlacePtr place) {
	places.insert(places.end(), place);
}

void Player::addTroops(ETroopsPtr troops) {

}

void Player::addRessource(GameRessourcePtr ressource) {

}

int Player::getRessourceCount(GameRessourcePtr ressource) {
	return 0;
}
