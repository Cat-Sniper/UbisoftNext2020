#include "stdafx.h"
#include "LevelManager.h"

LevelManager::LevelManager(Player* player) {
	m_player = player;
	m_currentLevel = new CircleLevel(m_player);
	m_levelColor = { 0.141f, 0.482f, 0.627f };
	
	
}

void LevelManager::Update(float deltaTime)
{
	m_currentLevel->Update(deltaTime);
}

void LevelManager::Draw()
{
	m_currentLevel->Draw();
}

LevelManager::~LevelManager() {
	delete m_currentLevel;
}