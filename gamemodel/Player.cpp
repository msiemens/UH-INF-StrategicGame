/*
 * Player.cpp
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#include <typeinfo>
#include <iostream>

#include "Player.h"
#include "gamemodel/entities/EArmy.h"
#include "gamemodel/entities/EPlace.h"

using namespace std;

Player::Player(int id) :
		playerId(id) {
}

Player::~Player() {
}

int Player::getPlayerId() {
	return playerId;
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

