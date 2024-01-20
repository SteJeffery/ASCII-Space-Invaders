#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../ASCII_GAME/Core/Renderer/AnimatedSprite.h"

class ASCIIRenderer;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

const int EnemyFrames = 4;

class Enemy : public AnimatedSprite
{
public:

	Enemy();
	~Enemy();

	void Initialise(Vector2& position, int sprite, int scoreValue, float initialTime = 0.0f);
	bool Update(float deltaTime);
	void Render(ASCIIRenderer* pRenderer);

	void Explode();

	bool Active() { return m_Active; }

	void MoveLeft();

	int GetScoreValue() { return m_ScoreValue; };

	int Move;

private:

	bool m_bInitialised;

	float m_AnimationTimer;
	bool m_Active;

	int m_ScoreValue;

};
#endif