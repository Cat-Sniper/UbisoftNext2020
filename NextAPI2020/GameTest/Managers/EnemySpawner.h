#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

class Level;

class EnemySpawner {
private:

	Level* ptr_level;
	EnemyType m_nextEnemy;
	int m_enemiesRemaining;

	
	int m_nLevelSections;
	Vec2 m_foregroundCenters[16];
	Vec2 m_backgroundCenters[16];
	
	float m_timeBetweenSpawns = 1500.0f;
	float m_timeAfterFinalSpawn = 4000.0f;

	float m_currentTime;
	float m_timeSinceLastSpawn;
	bool m_canSpawn = true;
	bool m_initEndOfLevel = false;

	float m_timeSinceFinalSpawn;


	void SpawnEnemy(EnemyType enemy);
	int PickRandomSection();
public:

	EnemySpawner(Level* level);
	~EnemySpawner();

	void Update(float deltaTime);
	void SetNextEnemyType(EnemyType enemy) { m_nextEnemy = enemy; }
	void AddEnemiesToSpawn(int remaining) { m_enemiesRemaining = remaining; }
	void InitializeSpawner(int nSections = 15, int nEnemies = 1);
};
#endif