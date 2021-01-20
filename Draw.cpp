#include "Draw.h"

void Draw::PointTo(int x, int y)
{
	gotoxy(x * 2, y);
}

void Draw::DrawPoint(int x, int y, string str)
{
	gotoxy(x * 2, y);
	cout << str;
	gotoxy(-1, -1);
}

void Draw::DrawBorder(int width, int height)
{
	PointTo(0, 0);
	for (int i = 0; i < width; i++)
	{
		cout << "¢Ë";
	}
	int i = 1;
	while (i < height - 1)
	{
		PointTo(0, i);
		cout << "¢Ë";
		PointTo(width - 1, i);
		cout << "¢Ë";
		i++;
	}
	PointTo(0, height - 1);
	for (int i = 0; i < width; i++)
	{
		cout << "¢Ë";
	}
}

void Draw::DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2; //x = x - str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}