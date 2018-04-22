#ifndef TILE_H
#define TILE_H

#include "global.h"

const int tileSize = 120;	// Sets the width/height, in pixels.

/*
 * Creates a tile, which will be filled with a 'X' or 'O'.
 */
class Tile
{
private:
	int type;
	
	SDL_Rect clip;
public:
	Tile ();
	Tile (int X, int Y);

	bool is_selected (int X, int Y);

	SDL_Rect Get_Clip ();

	int get_type();

	void set_type (int newType);
};

#endif