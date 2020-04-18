#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "InputManager.h"
#include "LevelManager.h"
#include "Renderer.h"
#include "Entities/Player.h"

class GameManager {

private:

	Player m_player;
	LevelManager m_levelManager;
	Renderer m_renderer;
	InputManager m_inputManager;

public:

	GameManager();
	void Update(float deltaTime);
	void Render();

	~GameManager();
};

#endif
