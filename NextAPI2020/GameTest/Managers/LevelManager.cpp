#include "stdafx.h"
#include "LevelManager.h"

#include "GameMath.h"
#include "Entities/Player.h"
#include "Managers/GameManager.h"

LevelManager::LevelManager(Player* player, GameManager* gameManager) {
	ptr_player = player;
	ptr_gameManager = gameManager;
	m_currentLevel = NULL;

	// Level Select
	m_currentLevelIndex = 3;
	m_numEnemies = 4; 
}

void LevelManager::Update(float deltaTime)
{
	m_currentLevel->Update(deltaTime);
}

void LevelManager::Draw()
{
	m_currentLevel->Draw();
}

void LevelManager::LoadLevel()
{	

	
	m_numEnemies++;

	if (m_currentLevel != NULL) delete m_currentLevel;
	if (m_currentLevelIndex >= m_numLevels) {
		m_currentLevelIndex = 0;
		m_colorScheme++;
		if (m_colorScheme >= 5) m_colorScheme = 0;
	}
	

	switch (m_currentLevelIndex) {
	case 0:
		m_currentLevel = new SquareLevel(ptr_player, ptr_gameManager);
		break;
	case 1:
		m_currentLevel = new CircleLevel(ptr_player, ptr_gameManager);
		break;
	case 2:
		m_currentLevel = new CrossLevel(ptr_player, ptr_gameManager);
		break;

	case 3:
		m_currentLevel = new TriangleLevel(ptr_player, ptr_gameManager);
		break;
	}

	m_currentLevel->LoadLevel(m_colorschemes[m_colorScheme].level, m_colorschemes[m_colorScheme].player, m_numEnemies);

	m_currentLevelIndex++;
	m_completedLevels++;


	// Every 5 levels, increase the rate at which spikes move.
	if (m_completedLevels % 5 == 0) {
		m_currentLevel->IncreaseDifficulty();
	}
	
}

void LevelManager::ResetGame()
{
	m_completedLevels = 0;
	m_currentLevelIndex = 0;
	m_colorScheme = 0;
}

LevelManager::~LevelManager() {
	delete m_currentLevel;
}