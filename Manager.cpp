#include "Manager.h"

Manager::Manager()
{
	m_iOldClockSnake = clock();
	m_iOldClockFood = clock();
	m_iWidth = MAPSIZE_WIDTH;
	m_iHeight = MAPSIZE_HEIGHT;
	m_iScreenWidth = m_iWidth * 2 + 1;
	m_iScreenHeight = m_iHeight + 3;
	m_iPoint = 0;
	m_bFlag = false;
	m_iActSpeed = 300;
}


void Manager::Init()
{
	int select = 0;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", m_iScreenHeight, m_iScreenWidth);
	system(buf);

	while (select != 2)
	{
		system("cls");
		m_Draw.DrawBorder(m_iWidth, m_iHeight);
		ShowScore();
		Menu();
		cin >> select;
		switch ((MENU)select)
		{
		case MENU_PLAY:			
			Play();
			break;
		case MENU_EXIT:
			break;
		default:
			break;
		}
	}		
}

void Manager::Menu()
{
	m_Draw.DrawMidText("★★  Snake Game  ★★",m_iWidth, 6);
	m_Draw.DrawMidText("1. 게임 시작", m_iWidth, 9);
	m_Draw.DrawMidText("2. 게임 종료", m_iWidth, 12);
	m_Draw.DrawMidText("선택 : ", m_iWidth, 15);
}

void Manager::ShowScore()
{
	m_Draw.DrawMidText("Score : " + to_string(m_iPoint), m_iWidth, m_iHeight);
}

void Manager::Play()
{
	system("cls");
	m_Draw.DrawBorder(m_iWidth, m_iHeight);
	m_Block.MakeWall();
	m_Block.DrawWall();
	m_Snake.DrawHead();
	m_iPoint = 0;
	ShowScore();

	while (m_bFlag != true)
	{
		m_Snake.SetSnakeClock(clock());
		m_Block.SetFoodClock(clock());

		if (kbhit())
			m_Snake.Input();		
		
		if (m_Snake.GetDirection() != DIRECTION_N)
		{
			if(m_Snake.GetSnakeClock() - m_iOldClockSnake > m_iActSpeed)
			{
				m_Snake.EraseTail();
				m_Snake.EraseHead();
				m_Snake.Move();					
				if (PointUp(m_Snake, m_Block) == true)
					m_Snake.MakeTail();					
				m_Snake.DrawTail();
				m_Snake.DrawHead();
				m_iOldClockSnake = m_Snake.GetSnakeClock();
			}
			
		}

		if (m_Block.GetFoodClock() - m_iOldClockFood > 1000)
		{
			m_Block.MakeFood();
			m_iOldClockFood = m_Block.GetFoodClock();
			ActSpeedControl();
		}

		m_Snake.SnakeCollision();
		m_Block.WallCollision(m_Snake.GetHeadx(), m_Snake.GetHeady());
		CheckCollision();
	}
	m_Snake.ClearTail();
	m_Block.WallClear();
	m_Snake.SnakeReset();
	m_Block.ResetWallCollision();
	m_Block.ClearFood();
	m_iActSpeed = 300;
	m_bFlag = false;
	ShowGameOverText();
	m_Draw.gotoxy(34, m_iHeight + 1);
	system("pause");	
}

void Manager::CheckCollision()
{
	if (m_Snake.CheckCollision() == true || m_Block.CheckCollision() == true)
	{
		m_bFlag = true;
	}
}

bool Manager::PointUp(Snake& s, Block& b)
{
	if (b.DeleteFood(s.GetHeadx(), s.GetHeady()) == true)
	{
		m_iPoint++;
		ShowScore();		
		return true;
	}
	else
		return false;

}

void Manager::ShowGameOverText()
{
	m_Draw.DrawMidText("[    Game  Over    ]", m_iWidth, m_iHeight / 2);
}

void Manager::ActSpeedControl()
{
	m_iActSpeed = m_iActSpeed * 0.98;
}
