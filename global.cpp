#include "global.h"

int currentState = GS_NULL, nextState = GS_NULL;	// Sets the current GameState in use, and the next GameState to switch to.

SDL_Color fontColor = {0x00, 0x00, 0x00};			// Sets the default text colour.
SDL_Event mainEvent;								// Creates the event state to poll mouse/key inputs with.
SDL_Surface *screen = NULL;							// Sets the screen which will be drawn to the window.

TTF_Font *font = NULL;								// Sets the default font.
