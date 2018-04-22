#include "tile.h"
#include "functions.h"
#include "global.h"

/*
 * Constructor for the Tile class.
 */
Tile::Tile ()
{
	clip.h = tileSize;
	clip.w = tileSize;
	clip.x = 0;
	clip.y = 0;

	type = TILE_BLANK;
}

/*
* Constructor for the Tile class, with additional parameters for setting the position on screen.
*/
Tile::Tile (int X, int Y)
{
	clip.h = tileSize;
	clip.w = tileSize;
	clip.x = X;
	clip.y = Y;

	type = TILE_BLANK;
}

/*
 * Checks if 'x' and 'y' parameters are within the bounds of the Tile.
 */
bool Tile::is_selected (int X, int Y)
{
	if (X > clip.x && X < clip.x + clip.w && Y > clip.y && Y < clip.y + clip.h)
	{
		return true;
	}

	return false;
}

/*
 * Returns the bounding box for the Tile.
 */
SDL_Rect Tile::Get_Clip ()
{
	return clip;
}

/*
* Returns the Tile type (i.e. blank, 'X' or 'O').
*/
int Tile::get_type()
{
	return type;
}

/*
 * Sets the Tile type (i.e. blank, 'X' or 'O').
 */
void Tile::set_type (int newType)
{
	type = newType;
}