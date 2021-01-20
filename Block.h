#pragma once
#include "Head.h"
#include "Draw.h"

struct Wall
{
	int x;
	int y;
	string img = "■";
	
};

struct Food
{
	int x;
	int y;
	string img = "♡";
};

class Block
{
	vector<Wall> m_Wall;
	list<Food> m_Food; //재시작 할때 미생성 확인 수정요함
	Draw m_Draw;
	int m_ifoodClock;
	bool m_bCollision;
	
public:
	Block();
	void MakeWall();	
	void DrawWall();
	bool WallCollision(int x, int y);
	bool CheckCollision();
	void WallClear();
	void MakeFood();
	inline void SetFoodClock(int clock) { m_ifoodClock = clock; }
	inline int GetFoodClock() { return m_ifoodClock; }
	void DrawFood(Food f);
	bool DeleteFood(int x, int y);
	void ResetWallCollision();
	void ClearFood();

};

