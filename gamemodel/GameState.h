/*
 * GameState.h
 *
 *  Created on: 22.11.2012
 *      Author: Armend
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

using namespace std;

class GameState {
public:
	GameState();
	int GET_GameState();
	void SET_GameState(int GS);
	virtual ~GameState();
private:
	int aktivGS;
};

#endif /* GAMESTATE_H_ */
