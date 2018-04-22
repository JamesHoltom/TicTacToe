#ifndef GSTATE_H
#define GSTATE_H

#include "global.h"
#include "functions.h"
#include "tile.h"
#include "timer.h"

/*
 * Creates a generic gamestate, which when extended defines a specific portion of the game (e.g. the main menu, the splash screen, etc.).
 */
class GameState
{
public:
	virtual ~GameState () {};

	virtual void Event () = NULL;
	virtual void Logic () = NULL;
	virtual void Render () = NULL;
};

/*
 * Creates the splash screen at the start of the game.
 * After 3 seconds (stored as 3000 milliseconds), or if a key is pressed, the game will advance to the main menu.
 */
class GaSt_Intro : public GameState
{
private:
	int delay;

	SDL_Surface *background, *message;

	Timer introDelay;

public:
	GaSt_Intro ();
	~GaSt_Intro ();

	void Event ();
	void Logic ();
	void Render ();
};

/*
 * Creates the main menu.
 * Pressing 'Space' will advance to the game.
 */
class GaSt_Menu : public GameState
{
private:
	bool showMessage;

	int messageDelay;

	SDL_Surface *background, *title, *message;

	Timer messageFlash;

public:
	GaSt_Menu ();
	~GaSt_Menu ();

	void Event ();
	void Logic ();
	void Render ();
};

/*
 * Creates the game section.
 * After winning, pressing 'Space' will return to the main menu.
 */
class GaSt_Game : public GameState
{
private:
	bool selected;
	bool win;

	int currentPlayer;
	int result;
	int selectedTile;
	int turnCount;

	SDL_Surface *background, *message, *tileGrid, *tileX, *tileO;

	Tile *list[9];

public:
	GaSt_Game ();
	~GaSt_Game ();

	int Swap_Players (int player);

	void Event ();
	void Logic ();
	void Render ();
};

extern GameState *gState;				// The current GameState being acted upon.

void Set_State (int newState);
void Change_State ();

#endif