#pragma once
#include "Head.h"
#include "Draw.h"

enum DIRECTION
{
	DIRECTION_N = 0,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT = 4	
};

struct Head //이동능력을 가지고 주체적으로 움직임 //꼬리에 xy정보를 넘겨주자
{
	int x;
	int y;
	string headImage = "⊙";
	DIRECTION direction = DIRECTION_N;
};

struct Tail
{	
	int x;
	int y;	
	DIRECTION direction = DIRECTION_N;
	string tailImage = "●";
};

class Snake
{
	int m_iMovableWidth;
	int m_iMovableHeight;
	int m_iSnakeClock;
	bool m_bCollision;
	Head m_SnakeHead;
	vector<Tail> m_SnakeTail;
	Draw m_Draw;
public:
	Snake();
	void MakeTail();
	void Move();
	void Input();
	void DrawHead();
	void DrawTail();
	void EraseHead();
	void EraseTail();
	inline int GetHeadx() { return m_SnakeHead.x; }
	inline int GetHeady() { return m_SnakeHead.y; }
	inline int GetDirection() { return m_SnakeHead.direction; }
	inline int GetSnakeClock() { return m_iSnakeClock; }
	inline void SetSnakeClock(int clock) { m_iSnakeClock = clock; }
	void SnakeCollision();
	bool CheckCollision();
	void ClearTail();
	void SnakeReset();
};

