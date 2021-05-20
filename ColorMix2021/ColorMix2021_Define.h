#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cmath>
#include <memory.h>

using namespace std;

const int SCREEN_WIDTH = 1440;
const int SCREEN_HEIGHT = 720;

const int MAP_WIDTH = 22, MAP_HEIGHT = 12;

const int X_OFFSET = (SCREEN_WIDTH - 48 * MAP_WIDTH) / 2;
const int Y_OFFSET = (SCREEN_HEIGHT - 48 * MAP_HEIGHT) / 2;

/*texture color code #8000ff is for color keying.*/
/*color code variants: 0x80, 0xb0, 0xff, 0x58*/

namespace dir
{
	enum dir_straight
	{
		UP, LEFT, DOWN, RIGHT
	};
	enum dir_diagonal
	{
		UP_LEFT, LEFT_DOWN, DOWN_RIGHT, RIGHT_UP
	};

	int Opposite(int dir)
	{
		return (dir + 2) % 4;
	}
	int ClockwiseShift(int dir)
	{
		return (dir + 3) % 4;
	}
	int CounterClockwiseShift(int dir)
	{
		return (dir + 1) % 4;
	}
}

namespace type
{
	enum block_type
	{
		EMPTY, WALL, MIRROR, SHOOTER, COMBINER, SEPARATOR, TARGET, ERASER = 15
	};
}
namespace image
{
	enum block_image
	{
		EMPTY, WALL, ERASER,
		MIRROR_BASE_0, MIRROR_COLOR_0, MIRROR_BASE_1, MIRROR_COLOR_1, MIRROR_BASE_2, MIRROR_COLOR_2, MIRROR_BASE_3, MIRROR_COLOR_3,
		BEAM_0, BEAM_1,
		SHOOTER_BASE_0, SHOOTER_COLOR_0, SHOOTER_BASE_1, SHOOTER_COLOR_1, SHOOTER_BASE_2, SHOOTER_COLOR_2, SHOOTER_BASE_3, SHOOTER_COLOR_3,
		COMBINER_0, COMBINER_1, COMBINER_2, COMBINER_3,
		SEPARATOR_0, SEPARATOR_1, SEPARATOR_2, SEPARATOR_3,
		//TARGET_BASE_0, TARGET_BASE_1, TARGET_BASE_2, TARGET_BASE_3, TARGET_COLOR,
		NUMBER_OF_IMAGES
	};
}
enum block_color
{
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE
};

int divide(int a, int b)
{
	return (int)floor((float)a / (float)b);
}