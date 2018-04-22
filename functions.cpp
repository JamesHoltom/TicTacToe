#include "functions.h"
#include "global.h"
#include "tile.h"

/*
 * Initialises SDL, SDL_image and SDL_ttf.
 */
int full_init ()
{
	// Initialise SDL.
	if (SDL_Init (SDL_INIT_EVERYTHING) < 0)
	{
		return 1;
	}

	// Initialise SDL_ttf.
	if (TTF_Init () < 0)
	{
		return 1;
	}

	// Set up the window that will be drawn to.
	if ( (screen = SDL_SetVideoMode (screenWidth, screenHeight, screenBPP, SDL_HWSURFACE | SDL_DOUBLEBUF) ) == NULL)
	{
		return 1;
	}

	// Set up the default font for text.
	if ( (font = TTF_OpenFont ("C:\\Windows\\Fonts\\arial.ttf", 20) ) == NULL)
	{
		return 2;
	}

	return 0;
}

/*
 * Runs through all possible win situations on the board.
 */
int check_win (Tile *list[])
{
	/*
	 * i.e. XXX
	 *      ---
	 *      ---
	 */
	if (list[0]->get_type () == TILE_X && list[1]->get_type () == TILE_X && list[2]->get_type () == TILE_X)	
		return TILE_X;

	/*
	* i.e. OOO
	*      ---
	*      ---
	*/
	if (list[0]->get_type () == TILE_O && list[1]->get_type () == TILE_O && list[2]->get_type () == TILE_O) 
		return TILE_O;

	/*
	* i.e. ---
	*      XXX
	*      ---
	*/
	if (list[3]->get_type () == TILE_X && list[4]->get_type () == TILE_X && list[5]->get_type () == TILE_X)
		return TILE_X;

	/*
	* i.e. ---
	*      OOO
	*      ---
	*/
	if (list[3]->get_type () == TILE_O && list[4]->get_type () == TILE_O && list[5]->get_type () == TILE_O)
		return TILE_O;

	/*
	* i.e. ---
	*      ---
	*      XXX
	*/
	if (list[6]->get_type () == TILE_X && list[7]->get_type () == TILE_X && list[8]->get_type () == TILE_X)
		return TILE_X;

	/*
	* i.e. ---
	*      ---
	*      OOO
	*/
	if (list[6]->get_type () == TILE_O && list[7]->get_type () == TILE_O && list[8]->get_type () == TILE_O)
		return TILE_O;

	/*
	* i.e. X--
	*      X--
	*      X--
	*/
	if (list[0]->get_type () == TILE_X && list[3]->get_type () == TILE_X && list[6]->get_type () == TILE_X)
		return TILE_X;

	/*
	* i.e. O--
	*      O--
	*      O--
	*/
	if (list[0]->get_type () == TILE_O && list[3]->get_type () == TILE_O && list[6]->get_type () == TILE_O)
		return TILE_O;

	/*
	* i.e. -X-
	*      -X-
	*      -X-
	*/
	if (list[1]->get_type () == TILE_X && list[4]->get_type () == TILE_X && list[7]->get_type () == TILE_X)
		return TILE_X;

	/*
	* i.e. -O-
	*      -O-
	*      -O-
	*/
	if (list[1]->get_type () == TILE_O && list[4]->get_type () == TILE_O && list[7]->get_type () == TILE_O)
		return TILE_O;

	/*
	* i.e. --X
	*      --X
	*      --X
	*/
	if (list[2]->get_type () == TILE_X && list[5]->get_type () == TILE_X && list[8]->get_type () == TILE_X)
		return TILE_X;

	/*
	* i.e. --O
	*      --O
	*      --O
	*/
	if (list[2]->get_type () == TILE_O && list[5]->get_type () == TILE_O && list[8]->get_type () == TILE_O)
		return TILE_O;

	/*
	* i.e. X--
	*      -X-
	*      --X
	*/
	if (list[0]->get_type () == TILE_X && list[4]->get_type () == TILE_X && list[8]->get_type () == TILE_X)
		return TILE_X;

	/*
	* i.e. O--
	*      -O-
	*      --O
	*/
	if (list[0]->get_type () == TILE_O && list[4]->get_type () == TILE_O && list[8]->get_type () == TILE_O)
		return TILE_O;

	/*
	* i.e. --X
	*      -X-
	*      X--
	*/
	if (list[2]->get_type () == TILE_X && list[4]->get_type () == TILE_X && list[6]->get_type () == TILE_X)
		return TILE_X;

	/*
	* i.e. --O
	*      -O-
	*      O--
	*/
	if (list[2]->get_type () == TILE_O && list[4]->get_type () == TILE_O && list[6]->get_type () == TILE_O)
		return TILE_O;

	// I.e. no win situation has been made, so continue to the next turn.
	return TILE_BLANK;
}

/*
 * Load an image to memory.
 * Use 'key' to set alpha transparency, and 'r', 'g' and 'b' to define the transparent colour.
 */
SDL_Surface *load_image (std::string file, bool key, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Surface *loaded = NULL, *optimised = NULL;

	// Load the image.
	loaded = IMG_Load (file.c_str () );

	// Check if the image successfully loaded.
	if (loaded != NULL)
	{
		// Optimise the image for blitting with SDL.
		optimised = SDL_DisplayFormat (loaded);

		// Free the original image surface.
		SDL_FreeSurface (loaded);

		// Check if alpha transparency is enabled, and that we have a surface to use.
		if (optimised != NULL && key)
		{
			Uint32 colorKey = SDL_MapRGB (optimised->format, r, g, b);

			SDL_SetColorKey (optimised, SDL_SRCCOLORKEY, colorKey);
		}
	}

	return optimised;
}

/*
 * Draws the image at 'source' to the screen/surface 'dest' at the position 'x' and 'y'.
 * Use 'clip' to specify a portion of 'source' to draw.
 */
void apply_surface (int x, int y, SDL_Surface *source, SDL_Surface *dest, SDL_Rect *clip)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface (source, clip, dest, &offset);
}

/*
 * Frees all memory and closes SDL and SDL_ttf.
 */
void cleanup ()
{
	// Close SDL_ttf.
	TTF_CloseFont (font);
	TTF_Quit ();

	// Close SDL.
	SDL_Quit ();
}

/*
 * Resets the Tile grid to all blank tiles.
 */
void reset (Tile *list[])
{
	for (int i = 0; i < 9; i++)
	{
		list[i]->set_type (TILE_BLANK);
	}
}