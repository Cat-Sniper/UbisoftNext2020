#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "Managers/EnemySpawner.h"
// Forward Declaration
class Player;
class Bullet;
class Enemy;
class GameManager;

class Level {

#define LEVEL_VERTS 16
#define NUM_SECTIONS 16

protected:

	Player* ptr_player;
	GameManager* ptr_gameManager;
	EnemySpawner* m_enemySpawner;

	// Level Geometry: index binds the foreground to background
	Vec2 m_foregroundGeometry[LEVEL_VERTS];
	Vec2 m_backgroundGeometry[LEVEL_VERTS];

	int m_activeEnemies = 0;
	float m_biggestSectionLength = 0;
	float m_sectionLengths[NUM_SECTIONS];
	bool m_loops;
	bool m_hasMoved;
	int m_currentSection[2];				// index of the two vertices the player is touching. The left defines the section the player is in
									// i.e. section {0, 1} = 0, {1, 2} = 1 ... {14, 15} = 14, {15, 0} = 15
	Color m_levelColor;
	Color m_playerColor;
	
	float m_speedAdjustment = 0.0f;
	std::vector<Bullet*> m_bullets;
	std::vector<Enemy*>m_enemies;

	Vec2 playerPos;
	Vec2 centerPos;

	Vec2 GetForground(int i) { return m_foregroundGeometry[i]; }
	Vec2 GetBackground(int i) { return m_backgroundGeometry[i]; }

	
	Vec2 GetSectionNormal(int left, int right);

	void TransformPlayer(float deltaTime);
	void TransformBullet(Bullet* bullet);
	void TransformEnemy(Enemy* enemy);

	void PopulateSectionLengths();
	

public:

	Level(Player* player, GameManager* gameManager);
	void Update(float deltaTime);
	void Draw();
	void SpawnBullet(bool enemyBullet, Vec2 position);
	void SpawnEnemy(EnemyType enemy, Vec2 position, int left);
	void MoveLeft();
	void MoveRight();
	void SuperZapper();

	void SetLevelColor(Color levelColor) { m_levelColor = levelColor; }
	Vec2 GetSectionTop(int left, int right);
	Vec2 GetSectionBack(int left, int right);
	Vec2 GetSectionTop();
	int GetSectionLeft() { return m_currentSection[0]; }
	int GetSectionRight() { return m_currentSection[1]; }
	int GetVerts() { return LEVEL_VERTS; }
	bool DoesLoop() { return m_loops; }
	void IncreaseDifficulty();
	GameManager* GetManager() { return ptr_gameManager; }
	

	// The only function implemented by each individual level. 
	// Must instantiate Geometry, the level enemy spawner, then let the player know it is done loading so gameplay can commence
	virtual void LoadLevel(Color level, Color player, int numEnemies) = 0;
	
	

	virtual ~Level();
};
#endif