#include "Bullet.h"
#include "../ASCII_GAME/Core/Renderer/ConsoleColours.h"


CHAR_INFO BulletSprite[] =
{
    { ' ' , BACKGROUND_WHITE }, { ' ' , BACKGROUND_WHITE }, { ' ' , BACKGROUND_WHITE },{ ' ' , BACKGROUND_WHITE }, { ' ' , BACKGROUND_WHITE }, { ' ' , BACKGROUND_WHITE },
};

Bullet::Bullet()
	:m_bInitialised(false)
	, m_Active(true)
{

}

Bullet::~Bullet()
{

}

void Bullet::Initialise(Vector2 & position, Vector2 & velocity)
{
	m_Velocity = velocity;

	Sprite::Initialise(m_Velocity.x < 0.0f ? BulletSprite : BulletSprite, Vector2(6,1));

	Vector2 startPosition(position.x - (Sprite::GetSize().x / 2), position.y - (Sprite::GetSize().y / 2));
	SetPosition(startPosition);

	m_bInitialised = true;
}

void Bullet::Update()
{
	if (!m_bInitialised || !m_Active)
		return;

	SetPosition(Vector2(GetPosition().x - m_Velocity.y, GetPosition().y + m_Velocity.x));
}

void Bullet::Render(ASCIIRenderer * pRenderer)
{
	if (!m_bInitialised || !m_Active)
		return;

	Sprite::Render(pRenderer);
}

void Bullet::Explode()
{
	m_Active = false;
}
