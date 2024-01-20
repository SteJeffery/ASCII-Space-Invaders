#ifndef _HORDE_H_
#define _HORDE_H_

#include "Enemy.h"

class ASCIIRenderer;
class Game;

const int Enemies = 5;
const int Rows = 5;
const int Limit = 15;

class Horde
{
public:
	Horde();
	~Horde();

	void Initialise(Game* pGame);
	void Update();
	void Render(ASCIIRenderer* pRenderer);

	bool Collides(Sprite& otherSprite);

	int GetScore() { int retVal = m_ScoreEarned; m_ScoreEarned = 0; return retVal; }
	int GetNumActiveEnemies();

	bool Arrived();

private:

	Enemy m_Enemy[Rows][Enemies];

	float m_UpdateTimer;

	Game* m_pGame;

	int m_ScoreEarned;

};
#endif