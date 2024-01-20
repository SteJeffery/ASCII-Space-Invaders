#ifndef _PlayerShip_H_
#define _PlayerShip_H_

#include "../ASCII_GAME/Core/Renderer/Sprite.h"

class ASCIIRenderer;

extern const int SCREEN_HEIGHT;

class PlayerShip : public Sprite
{
public:

	PlayerShip();
	~PlayerShip();

	void Initialise(Vector2& position, int upKey, int downKey);
	void Update();
	void Render(ASCIIRenderer* pRenderer);

private:

	void MoveUp();
	void MoveDown();

	int m_UpKey;
	int m_DownKey;

	bool UpKeyPressed();
	bool DownKeyPressed();

	bool m_bInitialised;

};

#endif

