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

using namespace std;

Player::Player() :
		id(boost::uuids::random_generator()()),actionsleft(10),onturn(false),gold(1000),wood(1000),stone(1000) {
}

Player::~Player() {

}

boost::uuids::uuid Player::getPlayerId() {
	return id;
}


void Player::setPlayerId(boost::uuids::uuid new_id) {
	 this->id = new_id;
}

std::string Player::getPlayerIdStr() {
	std::stringstream ss;
	ss << getPlayerId();
	return ss.str();
}

void Player::addArmy(EArmyPtr army) {
	armies.push_back(army);
}

void Player::addLocation(ELocationPtr place) {
	places.push_back(place);
}

void Player::addUnit(EUnitPtr unit) {

}

void Player::setGold(int value){
	this->gold = value;
}
void Player::setWood(int value){
	this->wood = value;
}
void Player::setStone(int value){
	this->stone = value;
}
int Player::getGold(){
 return this->gold;
}
int Player::getWood(){
	 return this->wood;
}
int Player::getStone(){
	 return this->stone;
}


void Player::SetActionLeft(int x) {
	this->actionsleft = x;
}

int Player::GetActionLeft() {
	return this->actionsleft;
}

string Player::getImgPath(){
	return this->imgpath;
}
void Player::setImgPath(string path){
	this->imgpath=path;
}
