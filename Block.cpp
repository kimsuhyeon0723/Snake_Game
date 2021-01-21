#include "Block.h"

Block::Block()
{
	m_ifoodClock = clock();
	m_bCollision = false;
}

void Block::MakeWall()
{
	srand((unsigned int)time(NULL));
	const int count = MAPSIZE_WIDTH * MAPSIZE_HEIGHT / 30;

	Wall w[count];	

	for (int i = 0; i < count; i++)
	{
		w[i].x = rand() % (MAPSIZE_WIDTH - 2) + 1; //1~49
		w[i].y = rand() % (MAPSIZE_HEIGHT - 2) + 1; //1~29
		while(w[i].x == MAPSIZE_WIDTH / 2 && w[i].y == MAPSIZE_HEIGHT)
		{
			w[i].x = rand() % (MAPSIZE_WIDTH - 2) + 1; //1~49
			w[i].y = rand() % (MAPSIZE_HEIGHT - 2) + 1; //1~29
		}
		m_Wall.push_back(w[i]);
	}		
}

void Block::DrawWall()
{
	for (auto iter = m_Wall.begin(); iter != m_Wall.end(); iter++)
	{
		m_Draw.DrawPoint(iter->x, iter->y, iter->img);
	}	
}

bool Block::WallCollision(int x, int y)
{
	for (auto iter = m_Wall.begin(); iter != m_Wall.end(); iter++)
	{
		if (x == iter->x && y == iter->y)
		{
			m_bCollision = true;
			return m_bCollision;
		}
	}
}

bool Block::CheckCollision()
{
	return m_bCollision;
}

void Block::WallClear()
{
	m_Wall.clear();
}

void Block::MakeFood()
{
	if (m_Food.size() < 10)
	{
		Food f;
		f.x = rand() % (MAPSIZE_WIDTH - 2) + 1;
		f.y = rand() % (MAPSIZE_HEIGHT - 2) + 1;
		for (auto iter = m_Wall.begin(); iter != m_Wall.end(); iter++)
		{
			if (iter->x == f.x && iter->y == f.y)
			{
				f.x = rand() % (MAPSIZE_WIDTH - 2) + 1;
				f.y = rand() % (MAPSIZE_HEIGHT - 2) + 1;
				iter = m_Wall.begin();
			}
		}
		
		DrawFood(f);
		m_Food.push_back(f);
		m_ifoodClock = clock();
	}	
}

void Block::DrawFood(Food f)
{
	m_Draw.DrawPoint(f.x, f.y, f.img);
}

bool Block::DeleteFood(int x, int y)
{
	for (auto iter = m_Food.begin(); iter != m_Food.end(); iter++)
	{
		if (iter->x == x && iter->y == y)
		{
			iter = m_Food.erase(iter);
			return true;
		}

	}
	return false;
}


void Block::ResetWallCollision()
{
	m_bCollision = false;
}

void Block::ClearFood()
{
	m_Food.clear();
}