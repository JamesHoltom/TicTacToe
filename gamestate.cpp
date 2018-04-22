#include "gamestate.h"

GameState *gState = NULL;			// The current GameState being acted upon.

/*
 * Sets the next GameState to switch to.
 */
void Set_State (int newState)
{
	if (nextState != GS_EXIT)
	{
		nextState = newState;
	}
}

/*
 * Changes the GameState if a new one is set.
 */
void Change_State ()
{
	// Only change GameState if a new one is set.
	if (nextState != GS_NULL)
	{
		/*
		 * Only destroy the GameState if it is not 'Exit'.
		 * A valid GameState is always required, and everything will be destroyed at the end of the program.
		 */
		if (nextState != GS_EXIT)
		{
			delete gState;
		}

		// Create the new GameState.
		if (nextState == GS_INTRO)
			gState = new GaSt_Intro ();

		if (nextState == GS_MENU)
			gState = new GaSt_Menu ();

		if (nextState == GS_GAME)
			gState = new GaSt_Game ();
	}

	// Set the new current state.
	currentState = nextState;

	// Reset the next state.
	nextState = GS_NULL;
}

/*
* Constructor for 'Splash screen' GameState.
*/
GaSt_Intro::GaSt_Intro ()
{
	// Set the delay before moving on to the main menu to 3 seconds.
	delay = 3000;

	// Load the intro background.
	background = load_image ("images\\intro\\bg.png");

	// Set up the splash message.
	message = TTF_RenderText_Solid (font, "Developed by James Holtom", fontColor);

	// Start the timer for delaying the splash screen.
	introDelay.start ();
}

/*
 * Destroys the GameState.
 */
GaSt_Intro::~GaSt_Intro ()
{
	SDL_FreeSurface (message);
	SDL_FreeSurface (background);
}

/*
 * Handles any mouse/key input for the current GameState.
 * If a key is pressed (other than 'Escape'), the game will move on to the main menu.
 * Pressing 'Escape' will quit the program.
 */
void GaSt_Intro::Event ()
{
	if (mainEvent.type == SDL_KEYDOWN)
	{
		if (mainEvent.key.keysym.sym != SDLK_ESCAPE)
		{
			Set_State (GS_MENU);
		}
		else
		{
			Set_State (GS_EXIT);
		}
	}
}

/*
 * Handles the logic for the current GameState.
 * After 3 seconds (stored as 3000 milliseconds), the game will advance to the main menu.
 */
void GaSt_Intro::Logic ()
{
	// Move to the main menu when the timer reaches the delay.
	if (introDelay.get_ticks () > delay)
	{
		Set_State (GS_MENU);
	}
}

/*
 * Draws the contents of the current GameState to screen.
 */
void GaSt_Intro::Render ()
{
	// Draw the background.
	apply_surface (0, 0, background, screen);

	// Draw the splash text.
	apply_surface ( (screenWidth - message->w) / 2, (screenHeight - message->h) / 2, message, screen);
}

/*
* Constructor for 'Main menu' GameState.
*/
GaSt_Menu::GaSt_Menu ()
{
	// Set the delay to show/hide the 'Press to start' message every half-second.
	showMessage = false;
	messageDelay = 500;

	// Load the menu background.
	background = load_image ("images\\menu\\bg.png");

	// Load the title logo.
	title = load_image ("images\\menu\\title.png", true, 0xFF, 0xFF, 0x00);

	// Set up the 'Press to start' message.
	message = TTF_RenderText_Solid (font, "Press \'Space\' to start!", fontColor);

	// Start the timer for showing/hiding the message above.
	messageFlash.start ();
}

/*
* Destroys the GameState.
*/
GaSt_Menu::~GaSt_Menu ()
{
	SDL_FreeSurface (message);
	SDL_FreeSurface (title);
	SDL_FreeSurface (background);
}

/*
 * Handles the logic for the current GameState.
 * When pressing 'Space', the game will play.
 * Pressing 'Escape' will quit the program.
*/
void GaSt_Menu::Event ()
{
	if (mainEvent.type == SDL_KEYDOWN)
	{
		if (mainEvent.key.keysym.sym == SDLK_SPACE)
			Set_State (GS_GAME);

		if (mainEvent.key.keysym.sym == SDLK_ESCAPE)
			Set_State (GS_EXIT);
	}
}

/*
 * Handles the logic for the current GameState.
 */
void GaSt_Menu::Logic ()
{
	// Alternate displaying the 'Press to start' message every time the timer reaches the delay.
	if (messageFlash.get_ticks () > messageDelay)
	{
		showMessage = !showMessage;

		messageFlash.start ();
	}
}

/*
* Draws the contents of the current GameState to screen.
*/
void GaSt_Menu::Render ()
{
	// Draw the background.
	apply_surface (0, 0, background, screen);

	// Draw the title logo.
	apply_surface ( (screenWidth - title->w) / 2, 15, title, screen);

	// Draw the message, if it is to be displayed.
	if (showMessage)
		apply_surface ( (screenWidth - message->w) / 2, screenHeight - message->h - 15, message, screen);
}

/*
* Constructor for 'Main game' GameState.
*/
GaSt_Game::GaSt_Game ()
{
	selected = false;
	win = false;

	currentPlayer = TILE_X;
	selectedTile = -1;
	turnCount = 0;

	/*
	 * Set up the Tile grid.
	 * The first Tile starts at position 140px 30px.
	 */
	for (int t = 0; t < 9; t++)
	{
		list[t] = new Tile (140 + ( (t%3) * tileSize), 30 + ( (t/3) * tileSize) );
	}

	// Load the game background.
	background = load_image ("images\\game\\bg.png");

	// Load the 'X' and 'O' Tile images.
	tileX = load_image ("images\\tiles\\tileX.png", true, 0x00, 0xFF, 0xFF);
	tileO = load_image ("images\\tiles\\tileO.png", true, 0xFF, 0xFF, 0x00);

	// Load the Tile grid image.
	tileGrid = load_image ("images\\tiles\\tileGrid.png", false);

	// Set up the information at the bottom of the screen.
	message = TTF_RenderText_Solid (font, "Welcome! It's Player 1's turn.", fontColor);
}

/*
* Destroys the GameState.
*/
GaSt_Game::~GaSt_Game ()
{
	for (int d = 0; d < 9; d++)
	{
		delete list[d];
		list[d] = NULL;
	}

	SDL_FreeSurface (tileX);
	SDL_FreeSurface (tileO);
}

/*
 * End the current player's turn and move to the next player.
 */
int GaSt_Game::Swap_Players (int player)
{
	if (player == TILE_X)
		player = TILE_O;
	else
		player = TILE_X;

	// Update the information at the bottom to reflect the player change.
	std::stringstream playerMessage;
	playerMessage<< "It is now Player "<< player<< "'s Turn.";
	message = TTF_RenderText_Solid (font, playerMessage.str ().c_str (), fontColor);

	return player;
}

/*
 * Handles the logic for the current GameState.
 * Clicking with the mouse will check to see if any Tiles were selected.
 * When the game is won, pressing 'Space' will start a new game.
 * Pressing 'p' will return to the main menu.
 * Pressing 'Escape' will quit the program.
 */
void GaSt_Game::Event ()
{
	if (mainEvent.type == SDL_KEYDOWN)
	{
		if (mainEvent.key.keysym.sym == SDLK_ESCAPE)
			Set_State (GS_EXIT);

		if (mainEvent.key.keysym.sym == SDLK_p)
			Set_State (GS_MENU);

		if (mainEvent.key.keysym.sym == SDLK_SPACE && win)
		{
			reset (list);
					
			win = false;
					
			message = TTF_RenderText_Solid (font, "Welcome! It's Player 1's turn.", fontColor);
		}
	}
		
	if (mainEvent.type == SDL_MOUSEBUTTONDOWN && !win)
	{
		for (int id = 0; id < 9; id++)
		{
			if (list[id]->is_selected(mainEvent.motion.x, mainEvent.motion.y) )
			{
				selectedTile = id;

				selected = true;
			}
		}
	}
}

/*
* Handles the logic for the current GameState.
*/
void GaSt_Game::Logic ()
{
	// Check if a Tile has been selected.
	if (selected)
	{
		if (selectedTile > -1 && selectedTile < 9)
		{
			// Check if the selected Tile has already been claimed. If not, claim the Tile and switch players.
			if (list[selectedTile]->get_type () != TILE_BLANK)
			{
				message = TTF_RenderText_Solid (font, "Cannot place tile here. Select another tile.", fontColor);
			}
			else
			{
				list[selectedTile]->set_type (currentPlayer);

				turnCount++;
				
				currentPlayer = Swap_Players (currentPlayer);
			}
			
			selectedTile = -1;
		}

		// Check if a win situation has been met.
		result = check_win (list);

		if (result == TILE_X)
		{
			win = true;

			message = TTF_RenderText_Solid (font, "X wins! Press \'Space \' to play again.", fontColor);
		}
		if (result == TILE_O)
		{
			win = true;

			message = TTF_RenderText_Solid (font, "O wins! Press \'Space \' to play again.", fontColor);
		}
		if (result == TILE_BLANK && turnCount == 9)
		{
			win = true;

			message = TTF_RenderText_Solid (font, "Stalemate! Press \'Space \' to play again.", fontColor);
		}

		selected = false;
	}
}

/*
* Draws the contents of the current GameState to screen.
*/
void GaSt_Game::Render ()
{
	// Draw the background.
	apply_surface (0, 0, background, screen);

	// Draw the Tile grid.
	apply_surface (140, 30, tileGrid, screen);

	// Draw the information at the bottom.
	apply_surface ( (screenWidth - message->w)/2, 425, message, screen);

	// Draw each Tile, if any are claimed.
	for (int i = 0; i < 9; i++)
	{
		if (list[i]->get_type () == TILE_X)
		{
			apply_surface (list[i]->Get_Clip ().x, list[i]->Get_Clip ().y, tileX, screen);
		}
		else if (list[i]->get_type () == TILE_O)
		{
			apply_surface (list[i]->Get_Clip ().x, list[i]->Get_Clip ().y, tileO, screen);
		}
	}
}