#pragma once

#include "ColorMix2021_SDLSetup.h"

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
	unsigned short GetBlock(Pos pos) const;
	unsigned short GetBlock(int x, int y) const;
	void SetBlock(Pos pos, int number);
	void SetBlock(int x, int y, int number);
	int GetType(Pos pos) const;
	int GetType(int x, int y) const;
	int GetDir(Pos pos) const;
	int GetDir(int x, int y) const;
	int GetColor(Pos pos) const;
	int GetColor(int x, int y) const;
	int GetFixedInfo(Pos pos) const;
	int GetFixedInfo(int x, int y) const;
	int GetR(Pos pos) const;
	int GetR(int x, int y) const;
	int GetG(Pos pos) const;
	int GetG(int x, int y) const;
	int GetB(Pos pos) const;
	int GetB(int x, int y) const;
	void SetInfo(Pos pos, int num, int dir);
	void SetInfo(int x, int y, int num, int dir);
	void ClearInfo();
	int GetInfo(Pos pos, int dir) const;
	int GetInfo(int x, int y, int dir) const;
};
Scene scene;

class Beam
{
private:
	Pos source_;
	Pos end_;
	int dir_;
	int len_;
	Color color_;
public:
	Beam(int x = 0, int y = 0, int dir = 0, int r = 0, int g = 0, int b = 0);
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
	if (x < 0 || x >= MAP_WIDTH)
		printf("Pos::SetX Error");
	x_ = x;
}
void Pos::SetY(int y)
{
	if (y < 0 || y >= MAP_HEIGHT)
		printf("Pos::SetY Error");
	y_ = y;
}

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
	if (r != 0 && r != 1)
		printf("Pos::SetR Error");
	r_ = r;
}
void Color::SetG(int g)
{
	if (g != 0 && g != 1)
		printf("Pos::SetG Error");
	g_ = g;
}
void Color::SetB(int b)
{
	if (b != 0 && b != 1)
		printf("Pos::SetB Error");
	b_ = b;
}

unsigned short Scene::GetBlock(Pos pos) const
{
	if (pos.GetX() < 0 || pos.GetX() >= MAP_WIDTH || pos.GetY() < 0 || pos.GetY() >= MAP_HEIGHT)
	{
		return -1;
		printf("Scene::GetBlock Error\n");
	}
	return map_[pos.GetY()][pos.GetX()];
}
unsigned short Scene::GetBlock(int x, int y) const
{
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
	{
		return -1;
		printf("Scene::GetBlock Error\n");
	}
	return map_[y][x];
}
void Scene::SetBlock(Pos pos, int number)
{
	if (pos.GetX() < 0 || pos.GetX() >= MAP_WIDTH || pos.GetY() < 0 || pos.GetY() >= MAP_HEIGHT)
	{
		printf("Scene::SetBlock Error\n");
	}
	map_[pos.GetY()][pos.GetX()] = number;
}
void Scene::SetBlock(int x, int y, int number)
{
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
	{
		printf("Scene::SetBlock Error\n");
	}
	map_[y][x] = number;
}
int Scene::GetType(Pos pos) const
{
	if (pos.GetX() < 0 || pos.GetX() >= MAP_WIDTH || pos.GetY() < 0 || pos.GetY() >= MAP_HEIGHT)
	{
		return -1;
		printf("Scene::GetType Error\n");
	}
	return map_[pos.GetY()][pos.GetX()] & 0x000F;
}
int Scene::GetType(int x, int y) const
{
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
	{
		return -1;
		printf("Scene::GetType Error\n");
	}
	return map_[y][x] & 0x000F;
}
int Scene::GetDir(Pos pos) const
{
	return (map_[pos.GetY()][pos.GetX()] & 0x00F0) >> 4;
}
int Scene::GetDir(int x, int y) const
{
	return (map_[y][x] & 0x00F0) >> 4;
}
int Scene::GetColor(Pos pos) const
{
	return (map_[pos.GetY()][pos.GetX()] & 0x0F00) >> 8;
}
int Scene::GetColor(int x, int y) const
{
	return (map_[y][x] & 0x0F00) >> 8;
}
int Scene::GetFixedInfo(Pos pos) const
{
	return (map_[pos.GetY()][pos.GetX()] & 0xF000) >> 12;
}
int Scene::GetFixedInfo(int x, int y) const
{
	return (map_[y][x] & 0xF000) >> 12;
}
int Scene::GetR(Pos pos) const
{
	return (map_[pos.GetY()][pos.GetX()] & 1024) >> 10;
}
int Scene::GetR(int x, int y) const
{
	return (map_[y][x] & 1024) >> 10;
}
int Scene::GetG(Pos pos) const
{
	return (map_[pos.GetY()][pos.GetX()] & 512) >> 9;
}
int Scene::GetG(int x, int y) const
{
	return (map_[y][x] & 512) >> 9;
}
int Scene::GetB(Pos pos) const
{
	return (map_[pos.GetY()][pos.GetX()] & 256) >> 8;
}
int Scene::GetB(int x, int y) const
{
	return (map_[y][x] & 256) >> 8;
}
void Scene::SetInfo(Pos pos, int num, int dir)
{
	switch (dir)
	{
	case dir_straight::UP:
		info_[pos.GetY()][pos.GetX()] = info_[pos.GetY()][pos.GetX()] & 0x00FFFFFF;//해당 자리 0으로 지우기
		info_[pos.GetY()][pos.GetX()] += (num << 24);//해당 자리에 num정보 대입
		break;
	case dir_straight::LEFT:
		info_[pos.GetY()][pos.GetX()] = info_[pos.GetY()][pos.GetX()] & 0xFF00FFFF;
		info_[pos.GetY()][pos.GetX()] += (num << 16);
		break;
	case dir_straight::DOWN:
		info_[pos.GetY()][pos.GetX()] = info_[pos.GetY()][pos.GetX()] & 0xFFFF00FF;
		info_[pos.GetY()][pos.GetX()] += (num << 8);
		break;
	case dir_straight::RIGHT:
		info_[pos.GetY()][pos.GetX()] = info_[pos.GetY()][pos.GetX()] & 0xFFFFFF00;
		info_[pos.GetY()][pos.GetX()] += num;
		break;
	default:
		printf("Scene::SetInfo ERROR, invalid direction\n");
		break;
	}
}
void Scene::SetInfo(int x, int y, int num, int dir)
{
	switch (dir)
	{
	case dir_straight::UP:
		info_[y][x] = info_[y][x] & 0x00FFFFFF;//해당 자리 0으로 지우기
		info_[y][x] += (num << 24);//해당 자리에 num정보 대입
		break;
	case dir_straight::LEFT:
		info_[y][x] = info_[y][x] & 0xFF00FFFF;
		info_[y][x] += (num << 16);
		break;
	case dir_straight::DOWN:
		info_[y][x] = info_[y][x] & 0xFFFF00FF;
		info_[y][x] += (num << 8);
		break;
	case dir_straight::RIGHT:
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
	memset(scene.info_, 0, sizeof(scene.info_));
}
int Scene::GetInfo(Pos pos, int dir) const
{
	switch (dir)
	{
	case dir_straight::UP:
		return (info_[pos.GetY()][pos.GetX()] & 0xFF000000) >> 24;
	case dir_straight::LEFT:
		return (info_[pos.GetY()][pos.GetX()] & 0x00FF0000) >> 16;
	case dir_straight::DOWN:
		return (info_[pos.GetY()][pos.GetX()] & 0x0000FF00) >> 8;
	case dir_straight::RIGHT:
		return (info_[pos.GetY()][pos.GetX()] & 0x000000FF);
	default:
		printf("Scene::GetInfo ERROR, invalid direction\n");
		return -1;
	}
}
int Scene::GetInfo(int x, int y, int dir) const
{
	switch (dir)
	{
	case dir_straight::UP:
		return (info_[y][x] & 0xFF000000) >> 24;
	case dir_straight::LEFT:
		return (info_[y][x] & 0x00FF0000) >> 16;
	case dir_straight::DOWN:
		return (info_[y][x] & 0x0000FF00) >> 8;
	case dir_straight::RIGHT:
		return (info_[y][x] & 0x000000FF);
	default:
		printf("Scene::GetInfo ERROR, invalid direction\n");
		return -1;
	}
}

Beam::Beam(int x, int y, int dir, int r, int g, int b)
{
	source_.SetX(x), source_.SetY(y);
	dir_ = dir;
	len_ = -1;
	color_.SetR(r), color_.SetG(g), color_.SetB(b);
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
	case dir_straight::UP:
		do { y--, len_++; } while (scene.GetType(x, y) == type::EMPTY);
		break;
	case dir_straight::LEFT:
		do { x--, len_++; } while (scene.GetType(x, y) == type::EMPTY);
		break;
	case dir_straight::DOWN:
		do { y++, len_++; } while (scene.GetType(x, y) == type::EMPTY);
		break;
	case dir_straight::RIGHT:
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