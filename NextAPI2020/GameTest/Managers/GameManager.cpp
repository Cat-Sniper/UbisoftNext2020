//------------------------------------------------------------------------
// GameManager.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
#include "App/app.h"
#include "GameManager.h"


GameManager::GameManager() :
	m_player(),
	m_levelManager(&m_player),
	m_inputManager(this, &m_levelManager, &m_player)
{
	m_currentScore = 0;
}

void GameManager::Update(float deltaTime) 
{
	m_inputManager.Update(deltaTime);
	m_levelManager.Update(deltaTime);
}

void GameManager::Render() {

	
	m_player.Draw();
	m_levelManager.Draw();

	// Draw UI
	char textBuffer[64] = "";
	sprintf(textBuffer, "SCORE: %ul", m_currentScore);
	App::Print(10, APP_VIRTUAL_HEIGHT - 12, textBuffer, 0.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}

GameManager::~GameManager()
{

}

