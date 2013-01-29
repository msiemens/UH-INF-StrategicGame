/*
 * SMBattleResult.cpp
 *
 *  Created on: 21.01.2013
 *      Author: Meholli
 */

#include "network/messages/statemessages/SMBattleResult.h"


SMBattleResult::SMBattleResult() : winner(new EArmy), looser_coords(){

}

SMBattleResult::~SMBattleResult() {
	// TODO Auto-generated destructor stub
}

