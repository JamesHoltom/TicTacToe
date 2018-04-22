#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "global.h"
#include "tile.h"

int full_init ();
int check_win (Tile *list[]);
int swap_players (int player);

SDL_Surface *load_image (std::string file, bool key = false, Uint8 r = 0x00, Uint8 g = 0x00, Uint8 b = 0x00);

void apply_surface (int x, int y, SDL_Surface *source, SDL_Surface *dest, SDL_Rect *clip = NULL);
void cleanup ();
void reset (Tile *list[]);

#endif
