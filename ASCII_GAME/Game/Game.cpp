#include "Game.h"
#include <windows.h>
#include <iostream>
#include "../Core/Utils.h"
#include "../Core/Renderer/ASCIIRenderer.h"

const int SCREEN_WIDTH = 256; //Sets the size of the game screen
const int SCREEN_HEIGHT = 96;

#define VK_UP 	    0x26
#define VK_DOWN	    0x28
#define VK_SPACE	0x20

//Draws the sprites used for the menues
char* TitleSprite = "                                                                                                                                                                            dddddddd                                                                        AAA                 SSSSSSSSSSSSSSS         CCCCCCCCCCCCCIIIIIIIIIIIIIIIIIIII     IIIIIIIIII                                                                 d::::::d                                                                       A:::A              SS:::::::::::::::S     CCC::::::::::::CI::::::::II::::::::I     I::::::::I                                                                 d::::::d                                                                      A:::::A            S:::::SSSSSS::::::S   CC:::::::::::::::CI::::::::II::::::::I     I::::::::I                                                                 d::::::d                                                                     A:::::::A           S:::::S     SSSSSSS  C:::::CCCCCCCC::::CII::::::IIII::::::II     II::::::II                                                                 d:::::d                                                                     A:::::::::A          S:::::S             C:::::C       CCCCCC  I::::I    I::::I         I::::Innnn  nnnnnnnn vvvvvvv           vvvvvvvaaaaaaaaaaaaa      ddddddddd:::::d     eeeeeeeeeeee    rrrrr   rrrrrrrrr       ssssssssss             A:::::A:::::A         S:::::S            C:::::C                I::::I    I::::I         I::::In:::nn::::::::nnv:::::v         v:::::v a::::::::::::a   dd::::::::::::::d   ee::::::::::::ee  r::::rrr:::::::::r    ss::::::::::s           A:::::A A:::::A         S::::SSSS         C:::::C                I::::I    I::::I         I::::In::::::::::::::nnv:::::v       v:::::v  aaaaaaaaa:::::a d::::::::::::::::d  e::::::eeeee:::::eer:::::::::::::::::r ss:::::::::::::s         A:::::A   A:::::A         SS::::::SSSSS    C:::::C                I::::I    I::::I         I::::Inn:::::::::::::::nv:::::v     v:::::v            a::::ad:::::::ddddd:::::d e::::::e     e:::::err::::::rrrrr::::::rs::::::ssss:::::s       A:::::A     A:::::A          SSS::::::::SS  C:::::C                I::::I    I::::I         I::::I  n:::::nnnn:::::n v:::::v   v:::::v      aaaaaaa:::::ad::::::d    d:::::d e:::::::eeeee::::::e r:::::r     r:::::r s:::::s  ssssss       A:::::AAAAAAAAA:::::A            SSSSSS::::S C:::::C                I::::I    I::::I         I::::I  n::::n    n::::n  v:::::v v:::::v     aa::::::::::::ad:::::d     d:::::d e:::::::::::::::::e  r:::::r     rrrrrrr   s::::::s           A:::::::::::::::::::::A                S:::::SC:::::C                I::::I    I::::I         I::::I  n::::n    n::::n   v:::::v:::::v     a::::aaaa::::::ad:::::d     d:::::d e::::::eeeeeeeeeee   r:::::r                  s::::::s       A:::::AAAAAAAAAAAAA:::::A               S:::::S C:::::C       CCCCCC  I::::I    I::::I         I::::I  n::::n    n::::n    v:::::::::v     a::::a    a:::::ad:::::d     d:::::d e:::::::e            r:::::r            ssssss   s:::::s    A:::::A             A:::::A  SSSSSSS     S:::::S  C:::::CCCCCCCC::::CII::::::IIII::::::II     II::::::IIn::::n    n::::n     v:::::::v      a::::a    a:::::ad::::::ddddd::::::dde::::::::e           r:::::r            s:::::ssss::::::s  A:::::A               A:::::A S::::::SSSSSS:::::S   CC:::::::::::::::CI::::::::II::::::::I     I::::::::In::::n    n::::n      v:::::v       a:::::aaaa::::::a d:::::::::::::::::d e::::::::eeeeeeee   r:::::r            s::::::::::::::s  A:::::A                 A:::::AS:::::::::::::::SS      CCC::::::::::::CI::::::::II::::::::I     I::::::::In::::n    n::::n       v:::v         a::::::::::aa:::a d:::::::::ddd::::d  ee:::::::::::::e   r:::::r             s:::::::::::ss  AAAAAAA                   AAAAAAASSSSSSSSSSSSSSS           CCCCCCCCCCCCCIIIIIIIIIIIIIIIIIIII     IIIIIIIIIInnnnnn    nnnnnn        vvv           aaaaaaaaaa  aaaa  ddddddddd   ddddd    eeeeeeeeeeeeee   rrrrrrr              sssssssssss    ";
char* LoseSprite = "        GGGGGGGGGGGGG               AAA               MMMMMMMM               MMMMMMMMEEEEEEEEEEEEEEEEEEEEEE          OOOOOOOOO     VVVVVVVV           VVVVVVVVEEEEEEEEEEEEEEEEEEEEEERRRRRRRRRRRRRRRRR        GGG::::::::::::G              A:::A              M:::::::M             M:::::::ME::::::::::::::::::::E        OO:::::::::OO   V::::::V           V::::::VE::::::::::::::::::::ER::::::::::::::::R     GG:::::::::::::::G             A:::::A             M::::::::M           M::::::::ME::::::::::::::::::::E      OO:::::::::::::OO V::::::V           V::::::VE::::::::::::::::::::ER::::::RRRRRR:::::R   G:::::GGGGGGGG::::G            A:::::::A            M:::::::::M         M:::::::::MEE::::::EEEEEEEEE::::E     O:::::::OOO:::::::OV::::::V           V::::::VEE::::::EEEEEEEEE::::ERR:::::R     R:::::R G:::::G       GGGGGG           A:::::::::A           M::::::::::M       M::::::::::M  E:::::E       EEEEEE     O::::::O   O::::::O V:::::V           V:::::V   E:::::E       EEEEEE  R::::R     R:::::RG:::::G                        A:::::A:::::A          M:::::::::::M     M:::::::::::M  E:::::E                  O:::::O     O:::::O  V:::::V         V:::::V    E:::::E               R::::R     R:::::RG:::::G                       A:::::A A:::::A         M:::::::M::::M   M::::M:::::::M  E::::::EEEEEEEEEE        O:::::O     O:::::O   V:::::V       V:::::V     E::::::EEEEEEEEEE     R::::RRRRRR:::::R G:::::G    GGGGGGGGGG        A:::::A   A:::::A        M::::::M M::::M M::::M M::::::M  E:::::::::::::::E        O:::::O     O:::::O    V:::::V     V:::::V      E:::::::::::::::E     R:::::::::::::RR  G:::::G    G::::::::G       A:::::A     A:::::A       M::::::M  M::::M::::M  M::::::M  E:::::::::::::::E        O:::::O     O:::::O     V:::::V   V:::::V       E:::::::::::::::E     R::::RRRRRR:::::R G:::::G    GGGGG::::G      A:::::AAAAAAAAA:::::A      M::::::M   M:::::::M   M::::::M  E::::::EEEEEEEEEE        O:::::O     O:::::O      V:::::V V:::::V        E::::::EEEEEEEEEE     R::::R     R:::::RG:::::G        G::::G     A:::::::::::::::::::::A     M::::::M    M:::::M    M::::::M  E:::::E                  O:::::O     O:::::O       V:::::V:::::V         E:::::E               R::::R     R:::::R G:::::G       G::::G    A:::::AAAAAAAAAAAAA:::::A    M::::::M     MMMMM     M::::::M  E:::::E       EEEEEE     O::::::O   O::::::O        V:::::::::V          E:::::E       EEEEEE  R::::R     R:::::R  G:::::GGGGGGGG::::G   A:::::A             A:::::A   M::::::M               M::::::MEE::::::EEEEEEEE:::::E     O:::::::OOO:::::::O         V:::::::V         EE::::::EEEEEEEE:::::ERR:::::R     R:::::R   GG:::::::::::::::G  A:::::A               A:::::A  M::::::M               M::::::ME::::::::::::::::::::E      OO:::::::::::::OO           V:::::V          E::::::::::::::::::::ER::::::R     R:::::R     GGG::::::GGG:::G A:::::A                 A:::::A M::::::M               M::::::ME::::::::::::::::::::E        OO:::::::::OO              V:::V           E::::::::::::::::::::ER::::::R     R:::::R        GGGGGG   GGGGAAAAAAA                   AAAAAAAMMMMMMMM               MMMMMMMMEEEEEEEEEEEEEEEEEEEEEE          OOOOOOOOO                 VVV            EEEEEEEEEEEEEEEEEEEEEERRRRRRRR     RRRRRRR";
char* WinSprite = "YYYYYYY       YYYYYYY     OOOOOOOOO     UUUUUUUU     UUUUUUUU     WWWWWWWW                           WWWWWWWWIIIIIIIIIINNNNNNNN        NNNNNNNNY:::::Y       Y:::::Y   OO:::::::::OO   U::::::U     U::::::U     W::::::W                           W::::::WI::::::::IN:::::::N       N::::::NY:::::Y       Y:::::Y OO:::::::::::::OO U::::::U     U::::::U     W::::::W                           W::::::WI::::::::IN::::::::N      N::::::NY::::::Y     Y::::::YO:::::::OOO:::::::OUU:::::U     U:::::UU     W::::::W                           W::::::WII::::::IIN:::::::::N     N::::::NYYY:::::Y   Y:::::YYYO::::::O   O::::::O U:::::U     U:::::U       W:::::W           WWWWW           W:::::W   I::::I  N::::::::::N    N::::::N   Y:::::Y Y:::::Y   O:::::O     O:::::O U:::::D     D:::::U        W:::::W         W:::::W         W:::::W    I::::I  N:::::::::::N   N::::::N    Y:::::Y:::::Y    O:::::O     O:::::O U:::::D     D:::::U         W:::::W       W:::::::W       W:::::W     I::::I  N:::::::N::::N  N::::::N     Y:::::::::Y     O:::::O     O:::::O U:::::D     D:::::U          W:::::W     W:::::::::W     W:::::W      I::::I  N::::::N N::::N N::::::N      Y:::::::Y      O:::::O     O:::::O U:::::D     D:::::U           W:::::W   W:::::W:::::W   W:::::W       I::::I  N::::::N  N::::N:::::::N       Y:::::Y       O:::::O     O:::::O U:::::D     D:::::U            W:::::W W:::::W W:::::W W:::::W        I::::I  N::::::N   N:::::::::::N       Y:::::Y       O:::::O     O:::::O U:::::D     D:::::U             W:::::W:::::W   W:::::W:::::W         I::::I  N::::::N    N::::::::::N       Y:::::Y       O::::::O   O::::::O U::::::U   U::::::U              W:::::::::W     W:::::::::W          I::::I  N::::::N     N:::::::::N       Y:::::Y       O:::::::OOO:::::::O U:::::::UUU:::::::U               W:::::::W       W:::::::W         II::::::IIN::::::N      N::::::::N    YYYY:::::YYYY     OO:::::::::::::OO   UU:::::::::::::UU                 W:::::W         W:::::W          I::::::::IN::::::N       N:::::::N    Y:::::::::::Y       OO:::::::::OO       UU:::::::::UU                    W:::W           W:::W           I::::::::IN::::::N        N::::::N    YYYYYYYYYYYYY         OOOOOOOOO           UUUUUUUUU                       WWW             WWW            IIIIIIIIIINNNNNNNN         NNNNNNN";

Game::Game()
:m_pRenderer(NULL)
, m_GameState(E_GAME_STATE_MAIN_MENU)
, m_bInitialised(false)
, m_bExitApp(false)
, m_Score(0)
{
}

Game::~Game()
{
	SAFE_DELETE_PTR(m_pRenderer);
}

void Game::Initialise() //Initalises the game
{
	InitialiseRenderer();

	m_PlayerShip.Initialise(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 8), VK_UP, VK_DOWN);

	m_Bullet.Initialise(Vector2(m_PlayerShip.GetPosition().x + (m_PlayerShip.GetSize().x * 0.5f), m_PlayerShip.GetPosition().y - 2), Vector2(0, -BulletSpeed));

	m_Bullet.SetActive(false);

	m_Horde.Initialise(this);

	InitialiseMenu();
	InitialiseLose();
	InitialiseWin();

	for (int i = 0; i < 4; i++) 
	{
		m_Digit[i].Initialise(Vector2(7 + (i * 10), 7));
	}

	m_bInitialised = true;
}

void Game::InitialiseRenderer()
{
	m_pRenderer = new ASCIIRenderer();

	m_pRenderer->Initialise(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::InitialiseMenu()
{
	//Main Menu
	Vector2 titleSize(237, 17);
	m_Title.Initialise(TitleSprite, FOREGROUND_WHITE, titleSize);

	Vector2 startPosition(10, 38);
	m_Title.SetPosition(startPosition);
}

void Game::InitialiseLose()
{
	//Lose Game Screen
	Vector2 gameOverTitleSize(200, 16);
	m_Lose.Initialise(LoseSprite, FOREGROUND_WHITE, gameOverTitleSize);

	Vector2 gameOverPosition(25, 37);
	m_Lose.SetPosition(gameOverPosition);
}

void Game::InitialiseWin()
{
	//Win Game Screen
	Vector2 youWinTitleSize(143, 16);
	m_Win.Initialise(WinSprite, FOREGROUND_WHITE, youWinTitleSize);

	Vector2 youWinPosition(53, 37);
	m_Win.SetPosition(youWinPosition);
}

void Game::Run() //Runs the game
{
	while (!m_bExitApp)
	{
		Update();

		Render();

        Sleep(30);
	}
}

void Game::Update() //Updates the game
{
	if (GetKeyState(VK_ESCAPE) < 0)
	{
		m_bExitApp = true;
		return;
	}

	switch (m_GameState)
	{
	case E_GAME_STATE_MAIN_MENU:
	{
		UpdateMenu();
	}
	break;

	case E_GAME_STATE_IN_GAME:
	{
		UpdateGame();
	}
	break;

	case E_GAME_STATE_WIN_GAME:
	{
		UpdateWin();
	}
	break;
	case E_GAME_STATE_LOSE_GAME:
	{
		UpdateLose();
	}
	break;

	default:
	{
	}
	}
}

void Game::Render()
{
	//call this first
	m_pRenderer->ClearScreen();

	//render your game here
	switch (m_GameState)
	{
	case E_GAME_STATE_MAIN_MENU:
	{
		RenderMain();
	}
	break;

	case E_GAME_STATE_IN_GAME:
	{
		RenderGame();
	}
	break;

	case E_GAME_STATE_WIN_GAME:
	{
		RenderWin();
	}
	break;

	case E_GAME_STATE_LOSE_GAME:
	{
		RenderLose();
	}
	break;

	default:
	{
	}
	}

	//call this last
	m_pRenderer->Render();
}

void Game::UpdateBullet() //Updates the projectile used by the playership
{
	m_Bullet.Update();

	if (m_Bullet.GetPosition().x < 0 || m_Bullet.GetPosition().x > SCREEN_WIDTH)
	{
		m_Bullet.Explode();
	}

	if (m_Bullet.Active() && m_Horde.Collides(m_Bullet))
	{
		m_Score += m_Horde.GetScore();
		m_Bullet.Explode();
	}
}

void Game::FireBullet() //Fires the projectile
{
	m_Bullet.SetPosition(m_PlayerShip.GetPosition().x + (m_PlayerShip.GetSize().x * 0.5f), m_PlayerShip.GetPosition().y + 3);
	m_Bullet.SetActive();
}

void Game::RenderScore()
{
	for (int i = 0; i < 4; i++)
	{
		m_Digit[i].Render(m_pRenderer);
	}
}

void Game::RenderGame()
{
	m_PlayerShip.Render(m_pRenderer);

	m_Bullet.Render(m_pRenderer);

	m_Horde.Render(m_pRenderer);

	RenderScore();
}

void Game::RenderMain()
{
	m_Title.Render(m_pRenderer);
}

void Game::RenderLose()
{
	m_Lose.Render(m_pRenderer);
}

void Game::RenderWin()
{
	m_Win.Render(m_pRenderer);
}

void Game::UpdateScore()
{
	for (int i = 0; i < 4; i++)
	{
		m_Digit[i].Update(0.0f);
	}

	int ScoreValues[4];

	ScoreValues[3] = m_Score > 9999 ? 9 : m_Score % 10;
	ScoreValues[2] = m_Score > 9999 ? 9 : m_Score / 10 % 10;
	ScoreValues[1] = m_Score > 9999 ? 9 : m_Score / 100 % 10;
	ScoreValues[0] = m_Score > 9999 ? 9 : m_Score / 1000 % 10;

	m_Digit[0].SetDigitValue(ScoreValues[0]);
	m_Digit[1].SetDigitValue(ScoreValues[1]);
	m_Digit[2].SetDigitValue(ScoreValues[2]);
	m_Digit[3].SetDigitValue(ScoreValues[3]);
}

void Game::UpdateMenu()
{
	if (GetKeyState(VK_ESCAPE) < 0)
	{
		m_bExitApp = true;
	}

	if (GetKeyState(VK_RETURN) < 0)
	{
		m_GameState = E_GAME_STATE_IN_GAME;
	}
}

void Game::UpdateGame()
{
	m_PlayerShip.Update();
	m_Horde.Update();
	UpdateScore();

	if (GetKeyState(VK_SPACE) < 0)
	{
		if (!m_Bullet.Active())
		{
			FireBullet();
		}
	}

	UpdateBullet();
	CheckWin();
	CheckLose();
}

void Game::UpdateLose()
{
	if (GetKeyState(VK_ESCAPE) < 0)
	{
		m_bExitApp = true;
	}
}

void Game::UpdateWin()
{
	if (GetKeyState(VK_ESCAPE) < 0)
	{
		m_bExitApp = true;
	}
}

void Game::CheckWin()
{
	if (m_Horde.GetNumActiveEnemies() <= 0)
	{
		//player wins
		m_GameState = E_GAME_STATE_WIN_GAME;
	}
}

void Game::CheckLose()
{
	if (m_Horde.Arrived())
	{
		//player loses
		m_GameState = E_GAME_STATE_LOSE_GAME;
	}
}
