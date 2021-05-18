#pragma once

#include "ColorMix2021_SDLSetup.h"
#include "ColorMix2021_Define.h"

class Scene
{
private:
	unsigned int info_[MAP_HEIGHT][MAP_WIDTH] = { 0, }; //(상/좌/하/우 각 8비트)
	unsigned short map_[MAP_HEIGHT][MAP_WIDTH] = // (고정 여부 4비트) (공백/R/G/B 4비트) (방향 4비트) (종류 4비트)
	{
		{ 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001 },
		{ 0x0001, 0x1103, 0x1113, 0x1123, 0x1133, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x1102, 0x1112, 0x1122, 0x1132, 0x0001 },
		{ 0x0001, 0x1203, 0x1213, 0x1223, 0x1233, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x1202, 0x1212, 0x1222, 0x1232, 0x0001 },
		{ 0x0001, 0x1303, 0x1313, 0x1323, 0x1333, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x1302, 0x1312, 0x1322, 0x1332, 0x0001 },
		{ 0x0001, 0x1403, 0x1413, 0x1423, 0x1433, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x1402, 0x1412, 0x1422, 0x1432, 0x0001 },
		{ 0x0001, 0x1503, 0x1513, 0x1523, 0x1533, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x1502, 0x1512, 0x1522, 0x1532, 0x0001 },
		{ 0x0001, 0x1603, 0x1613, 0x1623, 0x1633, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x1602, 0x1612, 0x1622, 0x1632, 0x0001 },
		{ 0x0001, 0x1703, 0x1713, 0x1723, 0x1733, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x1702, 0x1712, 0x1722, 0x1732, 0x0001 },
		{ 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001 },
		{ 0x0001, 0x1004, 0x1014, 0x1024, 0x1034, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x1005, 0x1015, 0x1025, 0x1035, 0x0001 },
		{ 0x0001, 0x1000, 0x1000, 0x1000, 0x1000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x1000, 0x1000, 0x1000, 0x1000, 0x0001 },
		{ 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001 },
	};
public:
	unsigned short GetBlock(int x, int y) const;
	void SetBlock(int x, int y, int number);
	int GetType(int x, int y) const;
	int GetDir(int x, int y) const;
	int GetColor(int x, int y) const;
	int GetFixedInfo(int x, int y) const;
	int GetR(int x, int y) const;
	int GetG(int x, int y) const;
	int GetB(int x, int y) const;
	void MoveBlock(int x1, int y1, int x2, int y2);
	void SetInfo(int x, int y, int num, int dir);
	void ClearInfo();
	int GetInfo(int x, int y, int dir) const;
};
Scene scene;

unsigned short Scene::GetBlock(int x, int y) const
{
	if (0 <= x && x < MAP_WIDTH && 0 <= y && y < MAP_HEIGHT) return map_[y][x];
	else return -1;
}
void Scene::SetBlock(int x, int y, int number)
{
	if (0 <= x && x < MAP_WIDTH && 0 <= y && y < MAP_HEIGHT)
		map_[y][x] = number;
	else printf("set block ERROR\n");
}
int Scene::GetType(int x, int y) const
{
	if (0 <= x && x < MAP_WIDTH && 0 <= y && y < MAP_HEIGHT) return map_[y][x] & 0x000F;
	else return -1;
}
int Scene::GetDir(int x, int y) const
{
	return (map_[y][x] & 0x00F0) >> 4;
}
int Scene::GetColor(int x, int y) const
{
	return (map_[y][x] & 0x0F00) >> 8;
}
int Scene::GetFixedInfo(int x, int y) const
{
	return (map_[y][x] & 0xF000) >> 12;
}
int Scene::GetR(int x, int y) const
{
	return (map_[y][x] & 1024) >> 10;
}
int Scene::GetG(int x, int y) const
{
	return (map_[y][x] & 512) >> 9;
}
int Scene::GetB(int x, int y) const
{
	return (map_[y][x] & 256) >> 8;
}
void Scene::MoveBlock(int x1, int y1, int x2, int y2)
{
	map_[y2][x2] = map_[y1][x1];
	map_[y1][x1] = 0x0000;
}
void Scene::SetInfo(int x, int y, int num, int dir)
{
	switch (dir)
	{
	case UP:
		info_[y][x] = info_[y][x] & 0x00FFFFFF;//해당 자리 0으로 지우기
		info_[y][x] += (num << 24);//해당 자리에 num정보 대입
		break;
	case LEFT:
		info_[y][x] = info_[y][x] & 0xFF00FFFF;
		info_[y][x] += (num << 16);
		break;
	case DOWN:
		info_[y][x] = info_[y][x] & 0xFFFF00FF;
		info_[y][x] += (num << 8);
		break;
	case RIGHT:
		info_[y][x] = info_[y][x] & 0xFFFFFF00;
		info_[y][x] += num;
		break;
	default:
		printf("Scene::SetInfo ERROR, invalid direction\n");
		break;
	}
}
void Scene::ClearInfo()
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			info_[j][i] = 0;
		}
	}
}
int Scene::GetInfo(int x, int y, int dir) const
{
	switch (dir)
	{
	case UP:
		return (info_[y][x] & 0xFF000000) >> 24;
	case LEFT:
		return (info_[y][x] & 0x00FF0000) >> 16;
	case DOWN:
		return (info_[y][x] & 0x0000FF00) >> 8;
	case RIGHT:
		return (info_[y][x] & 0x000000FF);
	default:
		printf("Scene::GetInfo ERROR, invalid direction\n");
		return -1;
	}
}

class Pos
{
private:
	int x_;
	int y_;
public:
	int GetX() const;
	int GetY() const;
	void SetX(int x);
	void SetY(int y);
};
int Pos::GetX() const
{
	return x_;
}
int Pos::GetY() const
{
	return y_;
}
void Pos::SetX(int x)
{
	x_ = x;
}
void Pos::SetY(int y)
{
	y_ = y;
}

class Color
{
private:
	int r_;
	int g_;
	int b_;
public:
	int GetR() const;
	int GetG() const;
	int GetB() const;
	void SetR(int r);
	void SetG(int g);
	void SetB(int b);
};
int Color::GetR() const
{
	return r_;
}
int Color::GetG() const
{
	return g_;
}
int Color::GetB() const
{
	return b_;
}
void Color::SetR(int r)
{
	r_ = r;
}
void Color::SetG(int g)
{
	g_ = g;
}
void Color::SetB(int b)
{
	b_ = b;
}

class Beam
{
private:
	Pos source_;
	Pos end_;
	int dir_;
	int len_;
	Color color_;
public:
	Beam(int x = 1, int y = 1, int dir = 0);
	void SetBeam(int x, int y, int dir, int r, int g, int b);
	Pos CheckBeamEnd();
	Pos GetBeamSource() const;
	Pos GetBeamEnd() const;
	int GetBeamLen() const;
	int GetBeamDir() const;
	int GetBeamColor() const;
	int GetR() const;
	int GetG() const;
	int GetB() const;
	void ShowBeamInfo() const;
};
vector <Beam> lightBeam; //번호는 1번부터 시작. i번 beam은 인덱스 i-1에 위치함.

Beam::Beam(int x, int y, int dir)
{
	source_.SetX(x);
	source_.SetY(y);
	dir_ = dir;
	len_ = -1;
}
void Beam::SetBeam(int x, int y, int dir, int r, int g, int b)
{
	source_.SetX(x);
	source_.SetY(y);
	dir_ = dir;
	color_.SetR(r);
	color_.SetG(g);
	color_.SetB(b);
}
Pos Beam::CheckBeamEnd()
{
	len_ = -1;
	int x = source_.GetX();
	int y = source_.GetY();
	switch (dir_)
	{
	case UP:
		do { y--, len_++; } while (scene.GetType(x, y) == type::EMPTY);
		break;
	case LEFT:
		do { x--, len_++; } while (scene.GetType(x, y) == type::EMPTY);
		break;
	case DOWN:
		do { y++, len_++; } while (scene.GetType(x, y) == type::EMPTY);
		break;
	case RIGHT:
		do { x++, len_++; } while (scene.GetType(x, y) == type::EMPTY);
		break;
	default:
		printf("Scene::GetInfo ERROR, invalid direction\n");
		break;
	}
	end_.SetX(x);
	end_.SetY(y);
	return end_;
}
Pos Beam::GetBeamSource() const
{
	return source_;
}
Pos Beam::GetBeamEnd() const
{
	return end_;
}
int Beam::GetBeamLen() const
{
	return len_;
}
int Beam::GetBeamDir() const
{
	return dir_;
}
int Beam::GetBeamColor() const
{
	return color_.GetR() * 4 + color_.GetG() * 2 + color_.GetB();
}
int Beam::GetR() const
{
	return color_.GetR();
}
int Beam::GetG() const
{
	return color_.GetG();
}
int Beam::GetB() const
{
	return color_.GetB();
}
void Beam::ShowBeamInfo() const
{
	printf("%d %d %d %d   %d %d %d\n", source_.GetX(), source_.GetY(), dir_, len_, GetR(), GetG(), GetB());
}

namespace Simulation
{
	void CreateShooterBeam(int x, int y);
	unsigned char CreateMirroredBeam(int num);
	bool CreateCombinedBeam(int num);
	bool CreateSeparatedBeam(int num, int color);
	void SimulateBeam(int num);
	void SimulateAll();
};

void Simulation::CreateShooterBeam(int x, int y)
{
	Beam new_beam;
	int shooter_r, shooter_g, shooter_b;
	shooter_r = scene.GetR(x, y);
	shooter_g = scene.GetG(x, y);
	shooter_b = scene.GetB(x, y);
	int shooter_dir;
	shooter_dir = scene.GetDir(x, y);

	new_beam.SetBeam(x, y, shooter_dir, shooter_r, shooter_g, shooter_b);
	lightBeam.push_back(new_beam);
}
unsigned char Simulation::CreateMirroredBeam(int num) //4비트씩 각각 새로 생성된 광선의 방향, 새로 생성된 광선의 유무 반환
{
	Beam* prior_beam = &lightBeam[num - 1]; //인덱스이므로 1을 빼준다.

	int xpos, ypos, beam_dir, beam_r, beam_g, beam_b;
	Pos prior_end;
	prior_end = prior_beam->GetBeamEnd();
	xpos = prior_end.GetX(), ypos = prior_end.GetY();
	beam_dir = prior_beam->GetBeamDir();
	beam_r = prior_beam->GetR();
	beam_g = prior_beam->GetG();
	beam_b = prior_beam->GetB();

	Beam new_beam;
	int mirror_r, mirror_g, mirror_b;
	mirror_r = scene.GetR(xpos, ypos);
	mirror_g = scene.GetG(xpos, ypos);
	mirror_b = scene.GetB(xpos, ypos);

	int mirror_dir;
	mirror_dir = scene.GetDir(xpos, ypos);

	int new_beam_dir;
	switch (mirror_dir)
	{
	case UP_LEFT:
		if (beam_dir == DOWN) new_beam_dir = LEFT;
		else if (beam_dir == RIGHT) new_beam_dir = UP;
		else return false;
		break;
	case LEFT_DOWN:
		if (beam_dir == RIGHT) new_beam_dir = DOWN;
		else if (beam_dir == UP) new_beam_dir = LEFT;
		else return false;
		break;
	case DOWN_RIGHT:
		if (beam_dir == UP) new_beam_dir = RIGHT;
		else if (beam_dir == LEFT) new_beam_dir = DOWN;
		else return false;
		break;
	case RIGHT_UP:
		if (beam_dir == LEFT) new_beam_dir = UP;
		else if (beam_dir == DOWN) new_beam_dir = RIGHT;
		else return false;
		break;
	default:
		printf("Simualtion::CreateMirroredBeam ERROR, invalid direction\n");
		break;
	}
	new_beam.SetBeam(xpos, ypos, new_beam_dir, mirror_r && beam_r, mirror_g && beam_g, mirror_b && beam_b);

	if (new_beam.GetR() || new_beam.GetG() || new_beam.GetB())//색이 검은색이 아니라면 반환
	{
		if (scene.GetInfo(xpos, ypos, new_beam_dir) == 0)//처음 생성한다면 push_back
		{
			lightBeam.push_back(new_beam);
			scene.SetInfo(xpos, ypos, lightBeam.size(), new_beam_dir);
		}
		else
			lightBeam[scene.GetInfo(xpos, ypos, new_beam_dir) - 1] = new_beam;//아니라면 이미 존재하는 beam을 업데이트

		return (new_beam_dir << 4) | true;
	}
	else return false;
}
bool Simulation::CreateCombinedBeam(int num) //새로 생성된 광선의 유무 반환
{
	Beam* prior_beam = &lightBeam[num - 1]; //인덱스이므로 1을 빼준다.

	int xpos, ypos, beam_dir;
	Pos prior_end;
	prior_end = prior_beam->GetBeamEnd();
	xpos = prior_end.GetX(), ypos = prior_end.GetY();
	beam_dir = prior_beam->GetBeamDir();

	Beam* new_beam = new Beam;
	int combiner_dir;
	combiner_dir = scene.GetDir(xpos, ypos);

	int up = 0, left = 0, down = 0, right = 0;
	Beam* beam_up = NULL, * beam_left = NULL, * beam_down = NULL, * beam_right = NULL;
	int total_r = 0, total_g = 0, total_b = 0;

	if (combiner_dir == (beam_dir + 2) % 4) //출력 장치로 전달되었다면 종료
		return false;

	scene.SetInfo(xpos, ypos, num, (beam_dir + 2) % 4);//beam_dir과 반대값 전달

	if (combiner_dir != UP)
	{
		up = scene.GetInfo(xpos, ypos, UP);
		if (up != 0)
		{
			beam_up = &lightBeam[up - 1];
			total_r = total_r || beam_up->GetR();
			total_g = total_g || beam_up->GetG();
			total_b = total_b || beam_up->GetB();
		}
	}
	if (combiner_dir != LEFT)
	{
		left = scene.GetInfo(xpos, ypos, LEFT);
		if (left != 0)
		{
			beam_left = &lightBeam[left - 1];
			total_r = total_r || beam_left->GetR();
			total_g = total_g || beam_left->GetG();
			total_b = total_b || beam_left->GetB();
		}
	}
	if (combiner_dir != DOWN)
	{
		down = scene.GetInfo(xpos, ypos, DOWN);
		if (down != 0)
		{
			beam_down = &lightBeam[down - 1];
			total_r = total_r || beam_down->GetR();
			total_g = total_g || beam_down->GetG();
			total_b = total_b || beam_down->GetB();
		}
	}
	if (combiner_dir != RIGHT)
	{
		right = scene.GetInfo(xpos, ypos, RIGHT);
		if (right != 0)
		{
			beam_right = &lightBeam[right - 1];
			total_r = total_r || beam_right->GetR();
			total_g = total_g || beam_right->GetG();
			total_b = total_b || beam_right->GetB();
		}
	}
	new_beam->SetBeam(xpos, ypos, combiner_dir, total_r, total_g, total_b);

	if (scene.GetInfo(xpos, ypos, combiner_dir) == 0)
	{
		lightBeam.push_back(*new_beam);
		scene.SetInfo(xpos, ypos, lightBeam.size(), combiner_dir);
	}
	else
		lightBeam[scene.GetInfo(xpos, ypos, combiner_dir) - 1] = *new_beam;
	return true;
}
bool Simulation::CreateSeparatedBeam(int num, int color)//생성할 색 입력(R, G, B)
{
	Beam* prior_beam = &lightBeam[num - 1]; //인덱스이므로 1을 빼준다.

	int xpos, ypos;
	Pos prior_end;
	prior_end = prior_beam->GetBeamEnd();
	xpos = prior_end.GetX(), ypos = prior_end.GetY();

	int beam_dir, beam_r, beam_g, beam_b;
	beam_dir = prior_beam->GetBeamDir();
	beam_r = prior_beam->GetR();
	beam_g = prior_beam->GetG();
	beam_b = prior_beam->GetB();

	Beam new_beam;

	int separator_dir;
	separator_dir = scene.GetDir(xpos, ypos);

	int new_beam_dir;
	switch (color)
	{
	case RED:
		new_beam_dir = (separator_dir + 1) % 4;
		new_beam.SetBeam(xpos, ypos, new_beam_dir, beam_r, 0, 0);
		break;
	case GREEN:
		new_beam_dir = separator_dir;
		new_beam.SetBeam(xpos, ypos, new_beam_dir, 0, beam_g, 0);
		break;
	case BLUE:
		new_beam_dir = (separator_dir + 3) % 4;
		new_beam.SetBeam(xpos, ypos, new_beam_dir, 0, 0, beam_b);
		break;
	default:
		printf("Error: this color is not vaild.");
	}

	if (new_beam.GetR() || new_beam.GetG() || new_beam.GetB())//색이 검은색이 아니라면 반환
	{
		if (scene.GetInfo(xpos, ypos, new_beam_dir) == 0)//처음 생성한다면 push_back
		{
			lightBeam.push_back(new_beam);
			scene.SetInfo(xpos, ypos, lightBeam.size(), new_beam_dir);
		}
		else
			lightBeam[scene.GetInfo(xpos, ypos, new_beam_dir) - 1] = new_beam;//아니라면 이미 존재하는 beam을 업데이트

		return true;
	}
	else return false;
}
void Simulation::SimulateBeam(int num)
{
	Pos end;
	end = lightBeam[num - 1].CheckBeamEnd();
	switch (scene.GetType(end.GetX(), end.GetY()))
	{
	case type::WALL:
		return;
	case type::SHOOTER:
		return;
	case type::MIRROR:
	{
		int temp;
		temp = CreateMirroredBeam(num);
		if (temp & 0x0F)
		{
			int new_beam_dir = (temp & 0xF0) >> 4;
			num = scene.GetInfo(end.GetX(), end.GetY(), new_beam_dir);
			SimulateBeam(num);
		}
		else return;
		break;
	}
	case type::COMBINER://무한루프 문제 발생 가능
	{
		if (CreateCombinedBeam(num))
		{
			num = scene.GetInfo(end.GetX(), end.GetY(), scene.GetDir(end.GetX(), end.GetY()));
			SimulateBeam(num);
		}
		else return;
		break;
	}
	case type::SEPARATOR:
	{
		if (lightBeam[num - 1].GetBeamDir() != scene.GetDir(end.GetX(), end.GetY()))//입력 방향이 올바르지 않다면
			return;
		int _num;//덮어쓰기 방지
		if (CreateSeparatedBeam(num, RED))
		{
			_num = scene.GetInfo(end.GetX(), end.GetY(), (scene.GetDir(end.GetX(), end.GetY()) + 1) % 4);
			SimulateBeam(_num);
		}
		if (CreateSeparatedBeam(num, GREEN))
		{
			_num = scene.GetInfo(end.GetX(), end.GetY(), scene.GetDir(end.GetX(), end.GetY()));
			SimulateBeam(_num);
		}
		if (CreateSeparatedBeam(num, BLUE))
		{
			_num = scene.GetInfo(end.GetX(), end.GetY(), (scene.GetDir(end.GetX(), end.GetY()) + 3) % 4);
			SimulateBeam(_num);
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
		printf("Error: Light behaviour against this type of block has not been defined.\n");
		return;
	}
}
void Simulation::SimulateAll()
{
	//struckTargets = 0;

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

namespace Render
{
	const Uint8 alpha_value = 160;

	void RenderBackground();
	void RenderBeam();
	void RenderBlock();
	void RenderAll();
};

void Render::RenderBackground()
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			PNG_Image[image::EMPTY].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
		}
	}
}
void Render::RenderBeam()
{
	for (unsigned int i = 0; i < lightBeam.size(); i++)
	{
		int x, y;
		int len;
		int dir;
		x = lightBeam[i].GetBeamSource().GetX();
		y = lightBeam[i].GetBeamSource().GetY();
		len = lightBeam[i].GetBeamLen();
		dir = lightBeam[i].GetBeamDir();
		int r = 255 * lightBeam[i].GetR();
		int g = 255 * lightBeam[i].GetG();
		int b = 255 * lightBeam[i].GetB();

		Pos end;
		end = lightBeam[i].GetBeamEnd();
		int end_block_type;
		end_block_type = scene.GetType(end.GetX(), end.GetY());
		int block_dir;
		block_dir = scene.GetDir(end.GetX(), end.GetY());

		bool render_start = true;
		bool render_end = true;

		switch (end_block_type)
		{
		case type::WALL:
			break;
		case type::MIRROR:
			if ((block_dir == dir) || ((block_dir + 1) % 4 == dir)) //거울 뒷면에 맞았다면
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
		case UP:
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
		case LEFT:
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
		case DOWN:
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
		case RIGHT:
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
			printf("Rendering Beams ERROR, invalid direction\n");
			break;
		}
	}
}
void Render::RenderBlock()
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
				case UP_LEFT:
					PNG_Image[image::MIRROR_BASE_0].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::MIRROR_COLOR_0].setColor(r, g, b);
					PNG_Image[image::MIRROR_COLOR_0].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case LEFT_DOWN:
					PNG_Image[image::MIRROR_BASE_1].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::MIRROR_COLOR_1].setColor(r, g, b);
					PNG_Image[image::MIRROR_COLOR_1].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case DOWN_RIGHT:
					PNG_Image[image::MIRROR_BASE_2].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::MIRROR_COLOR_2].setColor(r, g, b);
					PNG_Image[image::MIRROR_COLOR_2].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case RIGHT_UP:
					PNG_Image[image::MIRROR_BASE_3].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::MIRROR_COLOR_3].setColor(r, g, b);
					PNG_Image[image::MIRROR_COLOR_3].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				default:
					printf("Rendering Block(Mirror) ERROR, invalid direction\n");
					break;
				}
				break;
			case type::SHOOTER:
				switch (scene.GetDir(i, j))
				{
				case UP:
					PNG_Image[image::SHOOTER_BASE_0].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::SHOOTER_COLOR_0].setColor(r, g, b);
					PNG_Image[image::SHOOTER_COLOR_0].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case LEFT:
					PNG_Image[image::SHOOTER_BASE_1].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::SHOOTER_COLOR_1].setColor(r, g, b);
					PNG_Image[image::SHOOTER_COLOR_1].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case DOWN:
					PNG_Image[image::SHOOTER_BASE_2].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::SHOOTER_COLOR_2].setColor(r, g, b);
					PNG_Image[image::SHOOTER_COLOR_2].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case RIGHT:
					PNG_Image[image::SHOOTER_BASE_3].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					PNG_Image[image::SHOOTER_COLOR_3].setColor(r, g, b);
					PNG_Image[image::SHOOTER_COLOR_3].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				default:
					printf("Rendering Block(Shooter) ERROR, invalid direction\n");
					break;
				}
				break;
			case type::COMBINER:
				switch (scene.GetDir(i, j))
				{
				case UP:
					PNG_Image[image::COMBINER_0].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case LEFT:
					PNG_Image[image::COMBINER_1].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case DOWN:
					PNG_Image[image::COMBINER_2].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case RIGHT:
					PNG_Image[image::COMBINER_3].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				default:
					printf("Rendering Block(Combiner) ERROR, invalid direction\n");
					break;
				}
				break;
			case type::SEPARATOR:
				switch (scene.GetDir(i, j))
				{
				case UP:
					PNG_Image[image::SEPARATOR_0].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case LEFT:
					PNG_Image[image::SEPARATOR_1].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case DOWN:
					PNG_Image[image::SEPARATOR_2].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				case RIGHT:
					PNG_Image[image::SEPARATOR_3].render(X_OFFSET + i * 48, Y_OFFSET + j * 48);
					break;
				default:
					printf("Rendering Block(Combiner) ERROR, invalid direction\n");
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
				printf("Rendering Block ERROR, invalid block type\n");
				break;
			}
		}
	}
}
void Render::RenderAll()
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