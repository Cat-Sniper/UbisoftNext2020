#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

// Forward Declaration
class GameManager;
class LevelManager;
class Player;

class InputManager {

private:

	GameManager* m_gameManager;
	LevelManager* m_levelManager;
	Player* m_player;

	
	float m_currentTime;

	const float m_moveDelay = 40.0f;
	const float m_shootDelay = 69.0f;
	float m_lastMovement;
	float m_lastShot;
	bool m_canMove;
	bool m_canShoot;

public:
	InputManager(GameManager *gameManager, LevelManager *levelManager, Player *player);
	void Update(float deltaTime);
	~InputManager();

};
#endif
