#pragma once

#include "ColorMix2021_Define.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//SDL_DisplayMode dm;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//The surface contained by the window
//SDL_Surface* gScreenSurface = NULL;

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	SDL_Texture* GetTexture()
	{
		return mTexture;
	}

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x80, 0x00, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}
void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

//Current displayed PNG image
LTexture PNG_Image[image::NUMBER_OF_IMAGES];

//LTexture scene[NUMBER_OF_SCENES];

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
//SDL_Surface* loadSurface(std::string path);

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		/*SDL_DisplayMode dm;

		if (SDL_GetDesktopDisplayMode(0, &dm))
		{
			printf("Error getting desktop display mode\n");
			success = false;
		}

		SCREEN_WIDTH = dm.w;
		SCREEN_HEIGHT = dm.h;

		X_OFFSET = (SCREEN_WIDTH - 48 * MAP_WIDTH) / 2;
		Y_OFFSET = (SCREEN_HEIGHT - 48 * MAP_HEIGHT) / 2;*/

		//Create window
		gWindow = SDL_CreateWindow("ColorMix_Alpha", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			/*if (SDL_GetDesktopDisplayMode(0, &dm))
			{
				printf("Error getting desktop display mode\n");
				success = false;
			}*/
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				/*else
				{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);
				}*/
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	if (!PNG_Image[image::EMPTY].loadFromFile("Sprites/Background.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::WALL].loadFromFile("Sprites/Wall.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::ERASER].loadFromFile("Sprites/Eraser.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::MIRROR_BASE_0].loadFromFile("Sprites/Mirror_Base_0.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::MIRROR_COLOR_0].loadFromFile("Sprites/Mirror_Color_0.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::MIRROR_BASE_1].loadFromFile("Sprites/Mirror_Base_1.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::MIRROR_COLOR_1].loadFromFile("Sprites/Mirror_Color_1.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::MIRROR_BASE_2].loadFromFile("Sprites/Mirror_Base_2.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::MIRROR_COLOR_2].loadFromFile("Sprites/Mirror_Color_2.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::MIRROR_BASE_3].loadFromFile("Sprites/Mirror_Base_3.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::MIRROR_COLOR_3].loadFromFile("Sprites/Mirror_Color_3.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::BEAM_0].loadFromFile("Sprites/Beam_0.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::BEAM_1].loadFromFile("Sprites/Beam_1.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::SHOOTER_BASE_0].loadFromFile("Sprites/Shooter_Base_0.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::SHOOTER_COLOR_0].loadFromFile("Sprites/Shooter_Color_0.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::SHOOTER_BASE_1].loadFromFile("Sprites/Shooter_Base_1.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::SHOOTER_COLOR_1].loadFromFile("Sprites/Shooter_Color_1.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::SHOOTER_BASE_2].loadFromFile("Sprites/Shooter_Base_2.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::SHOOTER_COLOR_2].loadFromFile("Sprites/Shooter_Color_2.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::SHOOTER_BASE_3].loadFromFile("Sprites/Shooter_Base_3.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::SHOOTER_COLOR_3].loadFromFile("Sprites/Shooter_Color_3.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::COMBINER_0].loadFromFile("Sprites/Combiner_0.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::COMBINER_1].loadFromFile("Sprites/Combiner_1.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::COMBINER_2].loadFromFile("Sprites/Combiner_2.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::COMBINER_3].loadFromFile("Sprites/Combiner_3.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::SEPARATOR_0].loadFromFile("Sprites/Separator_0.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::SEPARATOR_1].loadFromFile("Sprites/Separator_1.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::SEPARATOR_2].loadFromFile("Sprites/Separator_2.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::SEPARATOR_3].loadFromFile("Sprites/Separator_3.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	/*if (!PNG_Image[image::TARGET_BASE_0].loadFromFile("Sprites/Target_Base_0.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::TARGET_BASE_1].loadFromFile("Sprites/Target_Base_1.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::TARGET_BASE_2].loadFromFile("Sprites/Target_Base_2.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::TARGET_BASE_3].loadFromFile("Sprites/Target_Base_3.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}
	if (!PNG_Image[image::TARGET_COLOR].loadFromFile("Sprites/Target_Color.png"))
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}*/

	return success;
}

void close()
{
	//Free loaded image
	for (int i = 0; i < image::NUMBER_OF_IMAGES; i++)
		PNG_Image[i].free();

	//Destroy window   
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}