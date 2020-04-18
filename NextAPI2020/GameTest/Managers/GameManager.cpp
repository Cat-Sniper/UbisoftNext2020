//------------------------------------------------------------------------
// GameManager.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
#include "App/app.h"
#include "GameManager.h"


GameManager::GameManager() :
	m_player(),
	m_levelManager(&m_player),
	m_renderer(this, &m_levelManager, &m_player), 
	m_inputManager(this, &m_levelManager, &m_player)
{

}

void GameManager::Update(float deltaTime) 
{
	m_inputManager.Update(deltaTime);
	m_levelManager.Update(deltaTime);
}

void GameManager::Render() {

	
	m_renderer.DrawLevel();
	m_renderer.DrawPlayer();
}

GameManager::~GameManager()
{

}

