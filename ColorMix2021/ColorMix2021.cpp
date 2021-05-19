#include "ColorMix2021_Function.h"

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//whether change has occured
			bool change = true;

			//Event handler
			SDL_Event e;

			//mouse components
			int mx = 0, my = 0;

			struct movement
			{
				int x, y;
				short selection = 0x0000;//selected block
			}move;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					switch (e.type)
					{
					case SDL_QUIT:
						quit = true;
						break;
					case SDL_MOUSEBUTTONDOWN:
						if (e.button.button == SDL_BUTTON_LEFT)
						{
							SDL_GetMouseState(&mx, &my);
							int xpos, ypos;
							xpos = divide(mx - X_OFFSET, 48), ypos = divide(my - Y_OFFSET, 48);

							if (scene.GetFixedInfo(xpos, ypos) == 1)
							{
								move.selection = 0x0FFF & scene.GetBlock(xpos, ypos); // get rid of first 4 bits
							}
							else if (scene.GetFixedInfo(xpos, ypos) == 0 && scene.GetType(xpos, ypos) != type::WALL)
							{
								scene.SetBlock(xpos, ypos, move.selection);
								change = true;
							}
						}
						break;
					}
				}

				if (change)
				{
					simulation::SimulateAll();
					change = false;
				}
				render::RenderAll();
			}
		}

		//Free resources and close SDL
		close();

		return 0;
	}
}