#ifndef GLOBAL_H
#define GLOBAL_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>

enum TileType {TILE_BLANK, TILE_X, TILE_O};							// Sets the possible states in the Tile class.
enum GState {GS_NULL, GS_INTRO, GS_MENU, GS_GAME, GS_EXIT};			// Sets the possible states in the GameState class.
	
const int screenWidth = 640, screenHeight = 480;					// Sets the width/height of the window.
const int screenBPP = 32;											// Sets the bits-per-pixel for images loaded to memory.
const int framesPerSecond = 30;										// Sets the maximum frame rate.

extern int currentState, nextState;									// Sets the current GameState in use, and the next GameState to switch to.

extern SDL_Color fontColor;											// Sets the default text colour.
extern SDL_Event mainEvent;											// Creates the event state to poll mouse/key inputs with.
extern SDL_Surface *screen;											// Sets the screen which will be drawn to the window.

extern TTF_Font *font;												// Sets the default font.

#endif
