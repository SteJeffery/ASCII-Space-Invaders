
#include "PlayerShip.h"
#include "../ASCII_GAME/Core/Maths/Vector2.h"
#include "../ASCII_GAME/Core/Renderer/ConsoleColours.h"
#include <Windows.h>

const int MOVEMENT_SPEED = 4;

CHAR_INFO ShipSprite[] =
{
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
};

PlayerShip::PlayerShip()
	:m_UpKey(0)
	, m_DownKey(0)
	, m_bInitialised(false)
{
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::Initialise(Vector2& position, int upKey, int downKey)
{
	m_UpKey = upKey;
	m_DownKey = downKey;

	Sprite::Initialise(ShipSprite, Vector2(12, 8));

	Vector2 startPosition(0, 48);
	SetPosition(startPosition);

	m_bInitialised = true;
}

void PlayerShip::Update()
{
	if (!m_bInitialised)
		return;

	if (UpKeyPressed())
	{
		MoveUp();
	}

	if (DownKeyPressed())
	{
		MoveDown();
	}

}

void PlayerShip::Render(ASCIIRenderer* pRenderer)
{
	if (!m_bInitialised)
		return;

	Sprite::Render(pRenderer);
}

void PlayerShip::MoveUp()
{
	SetPosition(Vector2(GetPosition().x, GetPosition().y - MOVEMENT_SPEED));

	if (GetPosition().y < 12)
	{
		MoveDown();
	}
}

void PlayerShip::MoveDown()
{
	SetPosition(Vector2(GetPosition().x, GetPosition().y + MOVEMENT_SPEED));

	if (GetPosition().y + GetSize().y > SCREEN_HEIGHT)
	{
		MoveUp();
	}
}

bool PlayerShip::UpKeyPressed()
{
	return (GetKeyState(m_UpKey) < 0);
}

bool PlayerShip::DownKeyPressed()
{
	return (GetKeyState(m_DownKey) < 0);
}
