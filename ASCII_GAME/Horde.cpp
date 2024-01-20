#include "Horde.h"
#include "../ASCII_GAME/Game/Game.h"

float deltaTime = 1.0f / 30.0f;

const int ENEMY_SPACING_X = 7.0; //Sets the enemy spacing
const int ENEMY_SPACING_Y = 7.0;

Horde::Horde()
:m_UpdateTimer(0.0f)
, m_pGame(NULL)
, m_ScoreEarned(0)
{

}

Horde::~Horde()
{
}

void Horde::Initialise(Game * pGame) //Initialises the horde
{ 
	m_pGame = pGame;
	deltaTime = 1.0f / 10.0f;

	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Enemies; j++)
		{
			m_Enemy[i][j].Initialise(Vector2(ENEMY_SPACING_X + j * (12 + ENEMY_SPACING_X), Limit + ENEMY_SPACING_Y + i * (8 + ENEMY_SPACING_Y)), i, (Rows - i) * 200/*, (i+1.0f) * 0.3f*/);
		}
	}
}

void Horde::Update()
{
	//update enemy movement
	m_UpdateTimer += deltaTime;

	if (m_UpdateTimer >= 0.5f)
	{
		m_UpdateTimer -= 0.5f;

			for (int i = 0; i < Rows; i++)
			{
				for (int j = 0; j < Enemies; j++)
				{
					m_Enemy[i][j].MoveLeft();
				}
			}
	}

	//update enemy animations
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Enemies; j++)
		{
			if (m_Enemy[i][j].Update(deltaTime))
			{
				Bullet* pBullet = new Bullet();
				pBullet->Initialise(Vector2(m_Enemy[i][j].GetPosition().x + (m_Enemy[i][j].GetSize().x / 2.0f), m_Enemy[i][j].GetPosition().y + 1), Vector2(0, BulletSpeed));
			}
		}
	}

	for (int i = 0; i < Rows; i++)
	{
		for (int j = Enemies - 1; j >= 0; j--)
		{
			//check the right most ship in this row
			if (m_Enemy[i][j].Active())
			{
				if ((m_Enemy[i][j].GetPosition().x + (m_Enemy[i][j].GetSize().x)) == SCREEN_WIDTH / 2)
				{
					m_Enemy[i][j].Move = 5;
				}
			}
		}
	}
}

void Horde::Render(ASCIIRenderer * pRenderer)
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Enemies; j++)
		{
			m_Enemy[i][j].Render(pRenderer);
		}
	}
}

bool Horde::Collides(Sprite & otherSprite)
{
	bool collision = false;
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Enemies; j++)
		{
			if (m_Enemy[i][j].Active() && otherSprite.Collides(m_Enemy[i][j].GetCurrentSprite()))
			{
				collision = true;
				m_ScoreEarned += m_Enemy[i][j].GetScoreValue();
				m_Enemy[i][j].Explode();
			}
		}
	}

	return collision;
}

int Horde::GetNumActiveEnemies()
{
	int Active = 0;
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Enemies; j++)
		{
			if (m_Enemy[i][j].Active())
			{
				Active++;
			}
		}
	}

	return Active;
}

bool Horde::Arrived()
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = Enemies - 1; j >= 0; j--)
		{
			//check the right most ship in this row
			if (m_Enemy[i][j].Active())
			{
				if ((m_Enemy[i][j].GetPosition().x + (m_Enemy[i][j].GetSize().x)) <= 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}
