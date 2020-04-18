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

public:
	InputManager(GameManager *gameManager, LevelManager *levelManager, Player *player);
	void Update(float deltaTime);

	~InputManager();

};
#endif
