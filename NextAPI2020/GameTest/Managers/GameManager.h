#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "InputManager.h"
#include "LevelManager.h"
#include "Entities/Player.h"

class GameManager {

private:

	Player m_player;
	LevelManager m_levelManager;
	InputManager m_inputManager;

	long unsigned int m_currentScore;

public:

	GameManager();
	void Update(float deltaTime);
	void Render();

	void AddToScore(unsigned int score) { m_currentScore += score; }

	~GameManager();
};

#endif
