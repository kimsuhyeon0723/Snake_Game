#pragma once
#include "Head.h"

class Draw
{
public:
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	void PointTo(int x, int y);
	void DrawPoint(int x, int y, string str);
	void DrawBorder(int width, int height);
	void DrawMidText(string str, int x, int y);
};

