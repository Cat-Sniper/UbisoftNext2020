#include "stdafx.h"
#include "EnemySpawner.h"
#include "Entities/Levels/Level.h"
#include "Managers/GameManager.h"

void EnemySpawner::SpawnEnemy(EnemyType enemy)
{
	int sectionSpawn = PickRandomSection();
	Vec2 sectionPosition = GameMath::RandomPosition(m_backgroundCenters[sectionSpawn], m_foregroundCenters[sectionSpawn]);
	ptr_level->SpawnEnemy(enemy, sectionPosition, sectionSpawn);
}

EnemySpawner::EnemySpawner(Level* level)
{
	ptr_level = level;
	m_initEndOfLevel = false;
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::Update(float deltaTime)
{
	float elapsedTime = m_currentTime + deltaTime;

	if (m_canSpawn) {
		m_timeSinceLastSpawn = elapsedTime;
		SpawnEnemy(SPIKE);
		m_canSpawn = false;
		m_enemiesRemaining--;
	}

	if (elapsedTime - m_timeSinceLastSpawn > m_timeBetweenSpawns && m_enemiesRemaining > 0) {
		m_canSpawn = true;
	}

	if (m_enemiesRemaining == 0) {

		if (!m_initEndOfLevel) {
			m_initEndOfLevel = true;
			m_timeSinceFinalSpawn = elapsedTime;
		}

		if(elapsedTime - m_timeSinceFinalSpawn > m_timeAfterFinalSpawn)
			ptr_level->GetManager()->StartWarp();
	}

	m_currentTime = elapsedTime;

}


// NOTE: Initialize spawner AFTER level geometry
void EnemySpawner::InitializeSpawner(int nSections, int nEnemies)
{
	m_nLevelSections = nSections;
	m_enemiesRemaining = nEnemies;

	if (nEnemies % 5 == 0) {
		m_timeBetweenSpawns -= 10.0f;
		
		if (m_timeBetweenSpawns < 500.0f) m_timeBetweenSpawns = 500.0f;
	}
	m_currentTime = 0.0f;
	m_timeSinceLastSpawn = 0.0f;
	for (int i = 0; i < 16; i++) {
		m_foregroundCenters[i] = ptr_level->GetSectionTop(i, i + 1);
		m_backgroundCenters[i] = ptr_level->GetSectionBack(i, i + 1);
	}
}

int EnemySpawner::PickRandomSection() { return (rand()) / (RAND_MAX / (m_nLevelSections)); }