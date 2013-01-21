/*
 * Timer.h
 *
 *  Created on: 02.01.2013
 *      Author: Meholli
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <SDL/SDL.h>

namespace std {

class Timer {
private:
	//The clock time when the timer started
	int startTicks;
	//The ticks stored when the timer was paused
	int pausedTicks;

	//The timer status
	bool paused;
	bool started;
public:
	//Initializes variables
	Timer();
	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();
	//Gets the timer's time
	int get_ticks();
	//Checks the status of the timer
	bool is_started();
	bool is_paused(); };
}; /* namespace std */
#endif /* TIMER_H_ */
