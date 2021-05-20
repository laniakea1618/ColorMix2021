#pragma once

#include "ColorMix2021_SDLSetup.h"
#include "ColorMix2021_Class.h"

namespace simulation
{
	void CreateShooterBeam(Pos pos);
	void CreateShooterBeam(int x, int y);
	unsigned char CreateMirroredBeam(int num);
	bool CreateCombinedBeam(int num);
	bool CreateSeparatedBeam(int num, int color);
	void SimulateBeam(int num);
	void SimulateAll();
};

namespace render
{
	const Uint8 alpha_value = 160;

	void RenderBackground();
	void RenderBeam();
	void RenderBlock();
	void RenderAll();
};

void simulation::CreateShooterBeam(Pos pos)
{
	Beam new_beam(pos.GetX(), pos.GetY(), scene.GetDir(pos), scene.GetR(pos), scene.GetG(pos), scene.GetB(pos));
	lightBeam.push_back(new_beam);
}
void simulation::CreateShooterBeam(int x, int y)
{
	Beam new_beam(x, y, scene.GetDir(x, y), scene.GetR(x, y), scene.GetG(x, y), scene.GetB(x, y));
	lightBeam.push_back(new_beam);
}
unsigned char simulation::CreateMirroredBeam(int num) //4비트씩 각각 새로 생성된 광선의 방향, 새로 생성된 광선의 유무 반환
{
	Beam* prior_beam = &lightBeam[num - 1]; //인덱스이므로 1을 빼준다.

	Pos prior_end = prior_beam->GetBeamEnd();

	int beam_dir = prior_beam->GetBeamDir();
	int beam_r = prior_beam->GetR();
	int beam_g = prior_beam->GetG();
	int beam_b = prior_beam->GetB();

	int mirror_r = scene.GetR(prior_end);
	int mirror_g = scene.GetG(prior_end);
	int mirror_b = scene.GetB(prior_end);
	int mirror_dir = scene.GetDir(prior_end);

	int new_beam_dir;
	if (beam_dir == dir::Opposite(mirror_dir))
	{
		new_beam_dir = dir::CounterClockwiseShift(beam_dir);
	}
	else if (beam_dir == dir::CounterClockwiseShift(mirror_dir))
	{
		new_beam_dir = dir::ClockwiseShift(beam_dir);
	}
	else return false;

	Beam new_beam(prior_end.GetX(), prior_end.GetY(), new_beam_dir, mirror_r && beam_r, mirror_g && beam_g, mirror_b && beam_b);

	if (new_beam.GetR() || new_beam.GetG() || new_beam.GetB())//색이 검은색이 아니라면 반환
	{
		if (scene.GetInfo(prior_end, new_beam_dir) == 0)//처음 생성한다면 push_back
		{
			lightBeam.push_back(new_beam);
			scene.SetInfo(prior_end, lightBeam.size(), new_beam_dir);
		}
		else
			lightBeam[scene.GetInfo(prior_end, new_beam_dir) - 1] = new_beam;//아니라면 이미 존재하는 beam을 업데이트
		return (new_beam_dir << 4) | true;
	}
	else return false;
}
bool simulation::CreateCombinedBeam(int num) //색 변화 유무 반환
{
	Beam* prior_beam = &lightBeam[num - 1]; //인덱스이므로 1을 빼준다.

	Pos prior_end = prior_beam->GetBeamEnd();

	int beam_dir = prior_beam->GetBeamDir();
	int combiner_dir = scene.GetDir(prior_end);

	int up = 0, left = 0, down = 0, right = 0;
	Beam* beam_up = NULL, * beam_left = NULL, * beam_down = NULL, * beam_right = NULL;
	int total_r = 0, total_g = 0, total_b = 0;

	scene.SetInfo(prior_end, num, dir::Opposite(beam_dir));//beam_dir과 반대값 전달

	if (combiner_dir != dir::UP)
	{
		up = scene.GetInfo(prior_end, dir::UP);
		if (up != 0)
		{
			beam_up = &lightBeam[up - 1];
			total_r |= beam_up->GetR();
			total_g |= beam_up->GetG();
			total_b |= beam_up->GetB();
		}
	}
	if (combiner_dir != dir::LEFT)
	{
		left = scene.GetInfo(prior_end, dir::LEFT);
		if (left != 0)
		{
			beam_left = &lightBeam[left - 1];
			total_r |= beam_left->GetR();
			total_g |= beam_left->GetG();
			total_b |= beam_left->GetB();
		}
	}
	if (combiner_dir != dir::DOWN)
	{
		down = scene.GetInfo(prior_end, dir::DOWN);
		if (down != 0)
		{
			beam_down = &lightBeam[down - 1];
			total_r |= beam_down->GetR();
			total_g |= beam_down->GetG();
			total_b |= beam_down->GetB();
		}
	}
	if (combiner_dir != dir::RIGHT)
	{
		right = scene.GetInfo(prior_end, dir::RIGHT);
		if (right != 0)
		{
			beam_right = &lightBeam[right - 1];
			total_r |= beam_right->GetR();
			total_g |= beam_right->GetG();
			total_b |= beam_right->GetB();
		}
	}
	Beam new_beam(prior_end.GetX(), prior_end.GetY(), combiner_dir, total_r, total_g, total_b);

	if (scene.GetInfo(prior_end, combiner_dir) == 0)
	{
		lightBeam.push_back(new_beam);
		scene.SetInfo(prior_end, lightBeam.size(), combiner_dir);
		return true;
	}
	else
	{
		if (lightBeam[scene.GetInfo(prior_end, combiner_dir) - 1].GetBeamColor()
			== total_r * 4 + total_g * 2 + total_b) // 색 변화 없다면
		{
			return false;
		}
		else
		{
			lightBeam[scene.GetInfo(prior_end, combiner_dir) - 1] = new_beam;
			return true;
		}
	}
}
bool simulation::CreateSeparatedBeam(int num, int color)//생성할 색 입력(R, G, B)
{
	Beam* prior_beam = &lightBeam[num - 1]; //인덱스이므로 1을 빼준다.

	Pos prior_end = prior_beam->GetBeamEnd();

	int beam_dir = prior_beam->GetBeamDir();
	int beam_r = prior_beam->GetR();
	int beam_g = prior_beam->GetG();
	int beam_b = prior_beam->GetB();

	Beam new_beam;

	int separator_dir = scene.GetDir(prior_end);

	int new_beam_dir;
	switch (color)
	{
	case RED:
		new_beam_dir = dir::CounterClockwiseShift(separator_dir);
		new_beam.SetBeam(prior_end.GetX(), prior_end.GetY(), new_beam_dir, beam_r, 0, 0);
		break;
	case GREEN:
		new_beam_dir = separator_dir;
		new_beam.SetBeam(prior_end.GetX(), prior_end.GetY(), new_beam_dir, 0, beam_g, 0);
		break;
	case BLUE:
		new_beam_dir = dir::ClockwiseShift(separator_dir);
		new_beam.SetBeam(prior_end.GetX(), prior_end.GetY(), new_beam_dir, 0, 0, beam_b);
		break;
	default:
		printf("simulation::CreateSeparatedBeam Error: invaild color\n");
		new_beam_dir = -1;
	}

	if (new_beam.GetR() || new_beam.GetG() || new_beam.GetB())//색이 검은색이 아니라면 반환
	{
		if (scene.GetInfo(prior_end, new_beam_dir) == 0)//처음 생성한다면 push_back
		{
			lightBeam.push_back(new_beam);
			scene.SetInfo(prior_end, lightBeam.size(), new_beam_dir);
		}
		else
			lightBeam[scene.GetInfo(prior_end, new_beam_dir) - 1] = new_beam;//아니라면 이미 존재하는 beam을 업데이트

		return true;
	}
	else return false;
}
void simulation::SimulateBeam(int num)
{
	Pos end = lightBeam[num - 1].CheckBeamEnd();
	switch (scene.GetType(end))
	{
	case type::WALL:
		return;
	case type::SHOOTER:
		return;
	case type::MIRROR:
	{
		int temp = CreateMirroredBeam(num);
		if (temp & 0x0F)
		{
			int new_beam_dir = (temp & 0xF0) >> 4;
			num = scene.GetInfo(end, new_beam_dir);
			SimulateBeam(num);
		}
		else return;
		break;
	}
	case type::COMBINER:
	{
		if (scene.GetDir(end) == dir::Opposite(lightBeam[num - 1].GetBeamDir()))//if input direction is invalid
			return;
		else
		{
			if (CreateCombinedBeam(num)) //색 변화 있다면 다시 탐색
			{
				num = scene.GetInfo(end, scene.GetDir(end));
				SimulateBeam(num);
			}
			else return; //없다면 return
		}
		break;
	}
	case type::SEPARATOR:
	{
		if (lightBeam[num - 1].GetBeamDir() != scene.GetDir(end))//if input direction is invalid
			return;
		int new_num;
		if (CreateSeparatedBeam(num, RED))
		{
			new_num = scene.GetInfo(end, dir::CounterClockwiseShift(scene.GetDir(end)));
			SimulateBeam(new_num);
		}
		if (CreateSeparatedBeam(num, GREEN))
		{
			new_num = scene.GetInfo(end, scene.GetDir(end));
			SimulateBeam(new_num);
		}
		if (CreateSeparatedBeam(num, BLUE))
		{
			new_num = scene.GetInfo(end, dir::ClockwiseShift(scene.GetDir(end)));
			SimulateBeam(new_num);
		}
		break;
	}
	/*case type::TARGET://하나의 물체에 여러번 추적될 경우 문제 발생 가능
	{
		if (((lightBeam[num - 1].GetBeamDir() + 2) % 4 == level.GetDir(end.GetXpos(), end.GetYpos()))
			&& (lightBeam[num - 1].GetBeamColor() == level.GetColor(end.GetXpos(), end.GetYpos())))
		{
			if (++struckTargets == targetNumber[world_num][level_num])
				level_change = true;
		}
		else return;
		break;
	}*/
	default:
		printf("simulation::SimulateBeam Error: Light behaviour against this type of block has not been defined.\n");
		return;
	}
}
void simulation::SimulateAll()
{
	lightBeam.clear();
	scene.ClearInfo();
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (scene.GetType(i, j) == type::SHOOTER)
			{
				CreateShooterBeam(i, j);
				SimulateBeam(lightBeam.size());
			}
		}
	}
}

void render::RenderBackground()
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			PNG_Image[image::EMPTY].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
		}
	}
}
void render::RenderBeam()
{
	for (unsigned int i = 0; i < lightBeam.size(); i++)
	{
		int x = lightBeam[i].GetBeamSource().GetX();
		int y = lightBeam[i].GetBeamSource().GetY();
		int len = lightBeam[i].GetBeamLen();
		int dir = lightBeam[i].GetBeamDir();
		int r = 255 * lightBeam[i].GetR();
		int g = 255 * lightBeam[i].GetG();
		int b = 255 * lightBeam[i].GetB();

		Pos end = lightBeam[i].GetBeamEnd();
		int end_block_type = scene.GetType(end);
		int block_dir = scene.GetDir(end);

		bool render_start = true;
		bool render_end = true;

		switch (end_block_type)
		{
		case type::WALL:
			break;
		case type::MIRROR:
			if ((block_dir == dir) || (dir::ClockwiseShift(block_dir) == dir)) //거울 뒷면에 맞았다면
				render_end = false;
			break;
		case type::SHOOTER:
			if (block_dir == dir) //뒷면에 맞았다면
				render_end = false;
			break;
		case type::COMBINER:
			render_end = false;
			break;
		}

		switch (dir)
		{
		case dir::UP:
			if (!render_start)
				y--;
			for (int j = 1; j <= len + render_start + render_end; j++)
			{
				PNG_Image[image::BEAM_0].setColor(r, g, b);
				PNG_Image[image::BEAM_0].setAlpha(alpha_value);
				PNG_Image[image::BEAM_0].render(X_OFFSET + x * 48, Y_OFFSET + y * 48);
				y--;
			}
			break;
		case dir::LEFT:
			if (!render_start)
				x--;
			for (int j = 1; j <= len + render_start + render_end; j++)
			{
				PNG_Image[image::BEAM_1].setColor(r, g, b);
				PNG_Image[image::BEAM_1].setAlpha(alpha_value);
				PNG_Image[image::BEAM_1].render(X_OFFSET + x * 48, Y_OFFSET + y * 48);
				x--;
			}
			break;
		case dir::DOWN:
			if (!render_start)
				y++;
			for (int j = 1; j <= len + render_start + render_end; j++)
			{
				PNG_Image[image::BEAM_0].setColor(r, g, b);
				PNG_Image[image::BEAM_0].setAlpha(alpha_value);
				PNG_Image[image::BEAM_0].render(X_OFFSET + x * 48, Y_OFFSET + y * 48);
				y++;
			}
			break;
		case dir::RIGHT:
			if (!render_start)
				x++;
			for (int j = 1; j <= len + render_start + render_end; j++)
			{
				PNG_Image[image::BEAM_1].setColor(r, g, b);
				PNG_Image[image::BEAM_1].setAlpha(alpha_value);
				PNG_Image[image::BEAM_1].render(X_OFFSET + x * 48, Y_OFFSET + y * 48);
				x++;
			}
			break;
		default:
			printf("render::RenderBeam Error: invalid direction\n");
			break;
		}
	}
}
void render::RenderBlock()
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			int r = 255 * scene.GetR(i, j);
			int g = 255 * scene.GetG(i, j);
			int b = 255 * scene.GetB(i, j);

			switch (scene.GetType(i, j))
			{
			case type::EMPTY:
				break;
			case type::WALL:
				PNG_Image[image::WALL].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
				break;
			case type::ERASER:
				PNG_Image[image::ERASER].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
				break;
			case type::MIRROR:
				switch (scene.GetDir(i, j))
				{
				case dir::UP_LEFT:
					PNG_Image[image::MIRROR_BASE_0].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::MIRROR_COLOR_0].setColor(r, g, b);
					PNG_Image[image::MIRROR_COLOR_0].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case dir::DOWN_LEFT:
					PNG_Image[image::MIRROR_BASE_1].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::MIRROR_COLOR_1].setColor(r, g, b);
					PNG_Image[image::MIRROR_COLOR_1].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case dir::DOWN_RIGHT:
					PNG_Image[image::MIRROR_BASE_2].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::MIRROR_COLOR_2].setColor(r, g, b);
					PNG_Image[image::MIRROR_COLOR_2].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case dir::UP_RIGHT:
					PNG_Image[image::MIRROR_BASE_3].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::MIRROR_COLOR_3].setColor(r, g, b);
					PNG_Image[image::MIRROR_COLOR_3].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				default:
					printf("render::RenderBlock(Mirror) Error: invalid direction\n");
					break;
				}
				break;
			case type::SHOOTER:
				switch (scene.GetDir(i, j))
				{
				case dir::UP:
					PNG_Image[image::SHOOTER_BASE_0].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::SHOOTER_COLOR_0].setColor(r, g, b);
					PNG_Image[image::SHOOTER_COLOR_0].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case dir::LEFT:
					PNG_Image[image::SHOOTER_BASE_1].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::SHOOTER_COLOR_1].setColor(r, g, b);
					PNG_Image[image::SHOOTER_COLOR_1].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case dir::DOWN:
					PNG_Image[image::SHOOTER_BASE_2].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::SHOOTER_COLOR_2].setColor(r, g, b);
					PNG_Image[image::SHOOTER_COLOR_2].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case dir::RIGHT:
					PNG_Image[image::SHOOTER_BASE_3].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::SHOOTER_COLOR_3].setColor(r, g, b);
					PNG_Image[image::SHOOTER_COLOR_3].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				default:
					printf("render::RenderBlock(Shooter) Error: invalid direction\n");
					break;
				}
				break;
			case type::COMBINER:
				switch (scene.GetDir(i, j))
				{
				case dir::UP:
					PNG_Image[image::COMBINER_0].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case dir::LEFT:
					PNG_Image[image::COMBINER_1].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case dir::DOWN:
					PNG_Image[image::COMBINER_2].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case dir::RIGHT:
					PNG_Image[image::COMBINER_3].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				default:
					printf("render::RenderBlock(Combiner) Error: invalid direction\n");
					break;
				}
				break;
			case type::SEPARATOR:
				switch (scene.GetDir(i, j))
				{
				case dir::UP:
					PNG_Image[image::SEPARATOR_0].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case dir::LEFT:
					PNG_Image[image::SEPARATOR_1].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case dir::DOWN:
					PNG_Image[image::SEPARATOR_2].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case dir::RIGHT:
					PNG_Image[image::SEPARATOR_3].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				default:
					printf("render::RenderBlock(Combiner) Error: invalid direction\n");
					break;
				}
				break;
				/*case type::TARGET:
					switch (level.GetDir(i, j))
					{
					case UP:
						PNG_Image[image::TARGET_BASE_0].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
						PNG_Image[image::TARGET_COLOR].setColor(r, g, b);
						PNG_Image[image::TARGET_COLOR].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
						break;
					case LEFT:
						PNG_Image[image::TARGET_BASE_1].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
						PNG_Image[image::TARGET_COLOR].setColor(r, g, b);
						PNG_Image[image::TARGET_COLOR].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
						break;
					case DOWN:
						PNG_Image[image::TARGET_BASE_2].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
						PNG_Image[image::TARGET_COLOR].setColor(r, g, b);
						PNG_Image[image::TARGET_COLOR].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
						break;
					case RIGHT:
						PNG_Image[image::TARGET_BASE_3].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
						PNG_Image[image::TARGET_COLOR].setColor(r, g, b);
						PNG_Image[image::TARGET_COLOR].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
						break;
					default:
						printf("Rendering Block(Target) ERROR, invalid direction\n");
						break;
					}
					break;*/
			default:
				printf("render::RenderBlock Error: invalid block type\n");
				break;
			}
		}
	}
}
void render::RenderAll()
{
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	RenderBackground();
	RenderBeam();
	RenderBlock();

	//Update screen
	SDL_RenderPresent(gRenderer);
}