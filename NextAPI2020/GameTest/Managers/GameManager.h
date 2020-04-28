#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "InputManager.h"
#include "LevelManager.h"
#include "Entities/Player.h"

class GameManager {

private:
	
	GameState m_currentState;
	Player m_player;
	int m_livesRemaining;
	LevelManager m_levelManager;
	InputManager m_inputManager;

	long unsigned int m_currentScore;

	// Display Functions for each state
	void DisplayPauseMenu();
	void DisplayMainMenu();
	void DisplayGameUI();
	void DisplayWarping();

public:

	GameManager();
	void Update(float deltaTime);
	void Render();
	void AddToScore(unsigned int score) { m_currentScore += score; }

	// State Switching logic / update
	void StartGame();
	void Pause();
	void UnPause();
	void StartWarp();
	void GameOver();
	

	GameState GetCurrentState() { return m_currentState; }
	

	~GameManager();
};

#endif
