//------------------------------------------------------------------------
// GameManager.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
#include "App/app.h"
#include "GameManager.h"


void GameManager::DisplayPauseMenu()
{
	// Draw UI
	char textBuffer[64] = "";
	sprintf(textBuffer, "CONTINUE = 'Enter'");
	App::Print(APP_VIRTUAL_WIDTH / 2 , APP_VIRTUAL_HEIGHT / 2 + 30, textBuffer, 0.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);

	sprintf(textBuffer, "Exit = 'Esc'");
	App::Print(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2 - 30, textBuffer, 0.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}

void GameManager::DisplayMainMenu()
{
	// Draw UI
	char textBuffer[64] = "";
	sprintf(textBuffer, "PROSPERO: Press Enter / Start to begin.");
	App::Print(APP_VIRTUAL_WIDTH / 4, APP_VIRTUAL_HEIGHT / 2, textBuffer, 0.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
}

void GameManager::DisplayGameUI()
{

	// Draw Gameplay UI
	char textBuffer[64] = "";
	sprintf(textBuffer, "SCORE: %u", m_currentScore);
	App::Print(10, APP_VIRTUAL_HEIGHT - 24, textBuffer, 0.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
	
	sprintf(textBuffer, "LIVES REMAINING: %d", m_player.GetLives());
	App::Print(10, APP_VIRTUAL_HEIGHT - 34, textBuffer, 0.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_10);

	sprintf(textBuffer, "LEVEL: %d", m_levelManager.GetCurrentLevelNumber());
	App::Print(APP_VIRTUAL_WIDTH - 200, APP_VIRTUAL_HEIGHT - 18, textBuffer, 0.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);

}

GameManager::GameManager() :
	m_player(),
	m_levelManager(&m_player, this),
	m_inputManager(this, &m_levelManager, &m_player)
{
	m_currentScore = 0;
	m_currentState = MENU;
}

void GameManager::Update(float deltaTime) 
{

	m_inputManager.Update(deltaTime);

	switch (m_currentState) {
	case MENU:
		break;
	case PAUSED:
		break;
	case WARPING:
		break;
	case GAMEPLAY:
		m_levelManager.Update(deltaTime);
		m_player.Update(deltaTime);
		if (!m_player.HasLivesLeft()) {

			m_currentState = GAMEOVER;
		}
		break;
	case GAMEOVER:
		break;

	case LOAD:
		m_levelManager.LoadLevel();
		m_currentState = GAMEPLAY;
		break;
	}
	
}

void GameManager::Render() {
	switch (m_currentState) {
	case MENU:
		DisplayMainMenu();
		break;
	case PAUSED:
		DisplayPauseMenu();
		break;
	case WARPING:
	case GAMEPLAY: 

		m_player.Draw();
		m_levelManager.Draw();
		DisplayGameUI();
		break;

	case GAMEOVER:
		GameOver();
		break;
	
	}

	
}

// Initialization for game play elements
void GameManager::StartGame()
{
	m_player.Init();
	m_currentScore = 0;
	m_currentState = LOAD;
	m_levelManager.ResetGame();
}

void GameManager::Pause()
{

	m_currentState = PAUSED;
}

void GameManager::UnPause()
{

	m_currentState = GAMEPLAY;
}

void GameManager::StartWarp()
{
	
	m_currentState = LOAD;
}

void GameManager::GameOver()
{

	// Draw Gameplay UI
	char textBuffer[64] = "";
	sprintf(textBuffer, "GAME OVER!");
	App::Print(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2 + 50, textBuffer, 0.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	sprintf(textBuffer, "FINAL SCORE: %u", m_currentScore);
	App::Print(APP_VIRTUAL_WIDTH /2, APP_VIRTUAL_HEIGHT/2 + 30, textBuffer, 0.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);

	// Draw UI
	sprintf(textBuffer, "RESTART? Press 'Enter'");
	App::Print(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2, textBuffer, 0.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);

	sprintf(textBuffer, "EXIT = 'Esc'");
	App::Print(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2 - 30, textBuffer, 0.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}


GameManager::~GameManager()
{

}

