#ifndef _GAME_H_
#define _GAME_H

#include "GameStates.h"
#include "../Core/Renderer/Sprite.h"
#include <vector>
#include "../PlayerShip.h"
#include "../Horde.h"
#include "../Bullet.h"
#include "../Enemy.h"
#include "GameObjects/ScoreDisplay.h"

class ASCIIRenderer;

class Game
{
public:
	Game();
	~Game();

	void Initialise();
	void Run();

private:

	//Functions
	void InitialiseRenderer();
	void InitialiseMenu();
	void InitialiseLose();
	void InitialiseWin();
	void Update();
	void Render();
	void UpdateBullet();
	void FireBullet();
	void RenderScore();
	void RenderGame();
	void RenderMain();
	void RenderLose();
	void RenderWin();
	void UpdateScore();
	void UpdateMenu();
	void UpdateGame();
	void UpdateLose();
	void UpdateWin();
	void CheckWin();
	void CheckLose();

	//Variables
	ASCIIRenderer* m_pRenderer;
	E_GAME_STATE m_GameState;
	PlayerShip m_PlayerShip;
	Bullet m_Bullet;
	Enemy m_Enemy;
	ScoreDisplay m_Digit[4];
	Horde m_Horde;
	Sprite m_Title;
	Sprite m_Lose;
	Sprite m_Win;

	bool m_bInitialised;
	bool m_bExitApp;

	int m_Score;
};


#endif
