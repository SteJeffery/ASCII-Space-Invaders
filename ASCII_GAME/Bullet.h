#ifndef _BULLET_H_
#define _BULLET_H_

#include "../ASCII_GAME/Core/Renderer/Sprite.h"

class ASCIIRenderer;

const int BulletSpeed = 5;

class Bullet : public Sprite
{
public:

	Bullet();
	~Bullet();

	void Initialise(Vector2& position, Vector2& velocity);
	void Update();
	void Render(ASCIIRenderer* pRenderer);
	void Explode();

	void SetActive(bool active = true) { m_Active = active; };
	bool Active() { return m_Active; }

private:

	Vector2 m_Velocity;

	bool m_bInitialised;
	bool m_Active;

};
#endif