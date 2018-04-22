#ifndef TIMER_H
#define TIMER_H

#include "global.h"

/*
 * Creates a timer with start/stop and pause/resume functions.
 */
class Timer
{
private:
	bool m_started, m_paused;

	int m_ticks, m_pauseTicks;

public:
	Timer ();

	bool get_paused ();
	bool get_started ();

	int get_ticks ();

	void pause ();
	void resume ();
	void start ();
	void stop ();
};

#endif
