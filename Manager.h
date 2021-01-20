#pragma once
#include "Head.h"
#include "Block.h"
#include "Snake.h"
#include "Draw.h"

enum MENU
{
	MENU_PLAY = 1,
	MENU_EXIT
};

class Manager
{
	int m_iOldClockSnake;
	int m_iOldClockFood;
	int m_iWidth;
	int m_iHeight;
	int m_iPoint;
	int m_iScreenWidth;
	int m_iScreenHeight;
	float m_iActSpeed;
	bool m_bFlag;
	Snake m_Snake;
	Draw m_Draw;
	Block m_Block;
public:	
	void Init();
	void Menu();
	void ShowScore();
	void Play();
	void CheckCollision();
	bool PointUp(Snake& s, Block& b);
	void ShowGameOverText();
	void ActSpeedControl();
	Manager();
};

