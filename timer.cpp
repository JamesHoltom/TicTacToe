#include "timer.h"

/*
 * Constructor for the Timer class.
 */
Timer::Timer ()
{
	m_started = false;
	m_paused = false;

	m_ticks = 0;
	m_pauseTicks = 0;
}

/*
 * Checks if the timer is paused.
 */
bool Timer::get_paused ()
{
	return m_paused;
}

/*
 * Checks if the timer is running 
 * This returns true, even if the timer is paused.
 */
bool Timer::get_started ()
{
	return m_started;
}

/*
 * Returns the duration (in milliseconds) the timer has run for.
 */
int Timer::get_ticks ()
{
	// Actually return a value if the timer is running.
	if (m_started)
	{
		// Return the duration the time has been running/paused.
		if (m_paused)
		{
			return m_pauseTicks;
		}

		return SDL_GetTicks() - m_ticks;
	}

	return 0;
}

/*
 * Pauses the timer.
 * m_pauseTicks is set up to count the duration between now and when the timer was paused.
 */
void Timer::pause ()
{
	if (m_started && !m_paused)
	{
		m_paused = true;

		m_pauseTicks = SDL_GetTicks() - m_ticks;
	}
}

/*
 * Re-starts the timer if it is paused.
 * 
 */
void Timer::resume ()
{
	if (m_started && m_paused)
	{
		m_paused = false;

		m_ticks = SDL_GetTicks() - m_pauseTicks;
		m_pauseTicks = 0;
	}
}

/*
 * Starts the timer.
 * Additionally un-pauses the timer.
 */
void Timer::start ()
{
	m_started = true;
	m_paused = false;

	m_ticks = SDL_GetTicks();
	m_pauseTicks = 0;
}

/*
 * Stops the timer.
 * Resets both tick counts to 0.
 */
void Timer::stop ()
{
	m_started = false;
	m_paused = false;

	m_ticks = 0;
	m_pauseTicks = 0;
}
