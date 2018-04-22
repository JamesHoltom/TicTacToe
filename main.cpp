#include "global.h"
#include "functions.h"
#include "gamestate.h"
#include "tile.h"
#include "timer.h"

int main (int argc, char* args[] )
{
	// Initialise SDL.
	if (full_init () > 0)
	{
		return -1;
	}

	// Set the current GameState to the splash screen.
	currentState = GS_INTRO;
	gState = new GaSt_Intro ();

	int frame = 0;

	// Use Timers to track and cap the frame rate.
	Timer frameCap, frameRate, frameUpdate;
	frameCap.start ();
	frameRate.start ();
	frameUpdate.start ();

	while (currentState != GS_EXIT)
	{
		frameCap.start ();
		
		// Poll for any mouse/key events that need to be handled.
		while (SDL_PollEvent (&mainEvent) )
		{
			// Quit the program if the 'X' button on the window has been pressed.
			if (mainEvent.type == SDL_QUIT)
				Set_State (GS_EXIT);

			gState->Event ();
		}

		gState->Logic ();

		// Change GameState if required.
		Change_State ();

		gState->Render ();

		// Draw the window.
		if (SDL_Flip (screen) < 0)
		{
			return 3;
		}

		// Advance the frame number.
		frame++;

		// Update the window caption with the number of frames and the frame rate every second.
		if (frameUpdate.get_ticks () > 1000)
		{
			std::stringstream caption;
			caption<< "Frame: "<< frame<< ", FPS: "<< frame / (frameRate.get_ticks () / 1000);

			SDL_WM_SetCaption (caption.str ().c_str (), NULL);

			frameUpdate.start ();
		}

		// Delay until the frame rate cap has been reached/passed.
		if (frameCap.get_ticks () < 1000 / framesPerSecond)
		{
			SDL_Delay ( (1000 / framesPerSecond) - frameCap.get_ticks () );
		}
	}

	// Close SDL.
	cleanup ();

	return 0;
}