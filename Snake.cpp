#include "Snake.h"

Snake::Snake()
{
	m_iMovableWidth = MAPSIZE_WIDTH;
	m_iMovableHeight = MAPSIZE_HEIGHT;
	m_iSnakeClock = clock();
	m_bCollision = false;
	m_SnakeHead.x = m_iMovableWidth / 2;
	m_SnakeHead.y = m_iMovableHeight / 2;
	m_SnakeHead.headImage = "��";
	m_SnakeHead.direction = DIRECTION_N;
	
}

void Snake::MakeTail()
{
	Tail t;
	if (m_SnakeTail.empty())
	{
		MakingConditions(t, m_SnakeHead);		
	}
	else
	{
		MakingConditions(t, m_SnakeTail.back());
	}	
	m_SnakeTail.push_back(t);
}

void Snake::Move()
{
	if (m_SnakeHead.direction == DIRECTION_UP)//�Ӹ� ���� ��� �̵�
	{
		m_SnakeHead.y--;
	}
	else if (m_SnakeHead.direction == DIRECTION_DOWN)
	{
		m_SnakeHead.y++;
	}
	else if (m_SnakeHead.direction == DIRECTION_LEFT)
	{
		m_SnakeHead.x--;
	}
	else if (m_SnakeHead.direction == DIRECTION_RIGHT)
	{
		m_SnakeHead.x++;
	}

	if (!m_SnakeTail.empty())
	{
		for (auto iter = m_SnakeTail.begin(); iter != m_SnakeTail.end(); iter++) //�����Ȳ��� ���� ��� ������
		{
			if (iter->direction == DIRECTION_LEFT)
				iter->x--;
			else if (iter->direction == DIRECTION_RIGHT)
				iter->x++;
			else if (iter->direction == DIRECTION_UP)
				iter->y--;
			else if (iter->direction == DIRECTION_DOWN)
				iter->y++;
		}

		DIRECTION saveDirection = DIRECTION_N;

		for (auto iter = m_SnakeTail.begin(); iter != m_SnakeTail.end(); iter++)
		{
			//next�� ���� �ε����� �޾ƾ��Ұ��� ���� ����
			//tmp�� ������ �����ߴ��� �ޱ�
			if (iter != m_SnakeTail.begin())//2��° ���� �Ѱ��ִ� ����
			{
				DIRECTION tmpDireciton = DIRECTION_N;
				tmpDireciton = iter->direction;
				iter->direction = saveDirection;
				saveDirection = tmpDireciton;				
			}
			else
			{
				saveDirection = iter->direction;
				iter->direction = m_SnakeHead.direction;
			}
			
		}

	}	
	
	m_iSnakeClock = clock();
}

void Snake::Input()
{
	char ch = getch();
	switch (ch)
	{
	case 'a':
	case 'A':
		if (m_SnakeHead.direction != DIRECTION_RIGHT)
			m_SnakeHead.direction = DIRECTION_LEFT;
		break;
	case 'd':
	case 'D':
		if (m_SnakeHead.direction != DIRECTION_LEFT)
			m_SnakeHead.direction = DIRECTION_RIGHT;
		break;
	case 'w':
	case 'W':
		if (m_SnakeHead.direction != DIRECTION_DOWN)
			m_SnakeHead.direction = DIRECTION_UP;
		break;
	case 's':
	case 'S':
		if (m_SnakeHead.direction != DIRECTION_UP)
			m_SnakeHead.direction = DIRECTION_DOWN;
		break;
	default:
		break;
	}
}

void Snake::DrawHead()
{
	m_Draw.DrawPoint(m_SnakeHead.x, m_SnakeHead.y, m_SnakeHead.headImage);
}

void Snake::DrawTail()
{	
	if (!m_SnakeTail.empty())
	{
		for (auto iter = m_SnakeTail.begin(); iter != m_SnakeTail.end(); iter++)
		{
			m_Draw.DrawPoint(iter->x, iter->y, iter->tailImage);
		}
	}
}
	

void Snake::EraseHead()
{
	m_Draw.DrawPoint(m_SnakeHead.x, m_SnakeHead.y, "  ");
}

void Snake::EraseTail()
{
	if (!m_SnakeTail.empty())
	{
		m_Draw.DrawPoint(m_SnakeTail.back().x, m_SnakeTail.back().y, "  ");
	}	
}

void Snake::SnakeCollision()//�� ���, �ڽ� �浹
{
	if (m_SnakeHead.x == 0 || m_SnakeHead.y == 0 || m_SnakeHead.x == m_iMovableWidth - 1 || m_SnakeHead.y == m_iMovableHeight - 1)
	{
		m_bCollision = true;
	}
	else
	{
		for (auto iter = m_SnakeTail.begin(); iter != m_SnakeTail.end(); iter++)
		{
			if (m_SnakeHead.x == iter->x && m_SnakeHead.y == iter->y)
			{
				m_bCollision = true;
			}
		}
	}
	
}

bool Snake::CheckCollision()
{
	return m_bCollision;
}

void Snake::ClearTail()
{
	m_SnakeTail.clear();
}


void Snake::SnakeReset()
{
	m_SnakeHead.direction = DIRECTION_N;
	m_SnakeHead.x = m_iMovableWidth / 2;
	m_SnakeHead.y = m_iMovableHeight / 2;
	m_bCollision = false;
}

void Snake::MakingConditions(Tail& t, Head h)//������ġ�� ���� ���� //t�� ������� �ް�, h�� t�� ���� ��������
{
	if (h.direction == DIRECTION_LEFT)
	{
		t.x = ++h.x;
		t.y = h.y;
	}
	else if (h.direction == DIRECTION_RIGHT)
	{
		t.x = --h.x;
		t.y = h.y;
	}
	else if (h.direction == DIRECTION_UP)
	{
		t.x = h.x;
		t.y = ++h.y;
	}
	else if (h.direction == DIRECTION_DOWN)
	{
		t.x = h.x;
		t.y = --h.y;
	}
	t.direction = h.direction;
}

void Snake::MakingConditions(Tail& t, Tail back)//t�� �����, h�� t�� ���� ��������
{
	if (back.direction == DIRECTION_LEFT)
	{
		t.x = ++back.x;
		t.y = back.y;
	}
	else if (back.direction == DIRECTION_RIGHT)
	{
		t.x = --back.x;
		t.y = back.y;
	}
	else if (back.direction == DIRECTION_UP)
	{
		t.x = back.x;
		t.y = ++back.y;
	}
	else if (back.direction == DIRECTION_DOWN)
	{
		t.x = back.x;
		t.y = --back.y;
	}
	t.direction = back.direction;
}

void Snake::MovingConditions(Tail & t, Head h)
{
	//if
}