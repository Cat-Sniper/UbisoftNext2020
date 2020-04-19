#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "App/app.h"
#include "Entities/Bullet.h"
#include "Entities/Player.h"
#include "Entities/Enemies/Enemy.h"
#include "Managers/GameMath.h"

class Level {
protected:
	Vec2 m_foregroundGeometry[16];
	Vec2 m_backgroundGeometry[16];

	const int m_nVerts = 16;
	bool m_loops;
	bool m_hasMoved;
	int m_currentSection[2];				// index of the two vertices the player is touching. This defines the section the player is in
	Color m_levelColor;
	Color m_playerColor;
	Player* ptr_player;
	std::vector<Bullet*> m_bullets;
	std::vector<Enemy*>m_enemies;


	Vec2 playerPos;
	Vec2 centerPos;

	Vec2 GetForground(int i) { return m_foregroundGeometry[i]; }
	Vec2 GetBackground(int i) { return m_backgroundGeometry[i]; }

	virtual Vec2 GetSectionBack(int left, int right) = 0;
	virtual Vec2 GetSectionNormal(int left, int right) = 0;
	virtual Vec2 GetBulletDirection(int left, int right) = 0;
	


	virtual void TransformPlayer(float deltaTime) = 0;
	virtual void TransformBullet(Bullet* bullet) = 0;
	virtual void TransformEnemy(Enemy* enemy) = 0;


public:

	virtual void Update(float deltaTime) = 0;
	virtual void SpawnBullet(bool enemyBullet, Vec2 position) = 0;
	virtual void SpawnEnemy(EnemyType enemy, Vec2 position) = 0;
	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;

	void SetLevelColor(Color levelColor) { m_levelColor = levelColor; }
	virtual Vec2 GetSectionTop(int left, int right) = 0;
	virtual Vec2 GetSectionTop() = 0;
	int GetSectionLeft() { return m_currentSection[0]; }
	int GetSectionRight() { return m_currentSection[1]; }
	int GetVerts() { return m_nVerts; }
	Vec2 GetPlayerPos() { return ptr_player->GetPosition(); }
	bool DoesLoop() { return m_loops; }

	virtual void Draw() {

		// Draw foreground
		Vec2 startPosFor = GetForground(0);
		Vec2 startPosBack = GetBackground(0);

		for (int i = 1; i < m_nVerts; i++) {

			Vec2 endPosFor = GetForground(i);
			Vec2 endPosBack = GetBackground(i);

			// Draw lines: 
			App::DrawLine(startPosFor.x, startPosFor.y, endPosFor.x, endPosFor.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);			// forground
			App::DrawLine(startPosBack.x, startPosBack.y, endPosBack.x, endPosBack.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);		// background

			if(i - 1 == m_currentSection[0] || i - 1 == m_currentSection[1])
				App::DrawLine(startPosFor.x, startPosFor.y, startPosBack.x, startPosBack.y, m_playerColor.r, m_playerColor.g, m_playerColor.b);
			else App::DrawLine(startPosFor.x, startPosFor.y, startPosBack.x, startPosBack.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);		// connect back to for

			startPosFor = endPosFor;
			startPosBack = endPosBack;

			// Final position
			if (i == m_nVerts - 1) {

				if (m_currentSection[0] == m_nVerts - 1 || i == m_currentSection[1])
					App::DrawLine(startPosFor.x, startPosFor.y, startPosBack.x, startPosBack.y, m_playerColor.r, m_playerColor.g, m_playerColor.b);
				else App::DrawLine(startPosFor.x, startPosFor.y, startPosBack.x, startPosBack.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);		// connect back to for

				// Connect looped levels
				if (m_loops) {

					endPosFor = GetForground(0);
					endPosBack = GetBackground(0);

					App::DrawLine(startPosFor.x, startPosFor.y, endPosFor.x, endPosFor.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);
					App::DrawLine(startPosBack.x, startPosBack.y, endPosBack.x, endPosBack.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);
				}
			}
		}

		// Draw Bullets
		for (auto &i : m_bullets) {
			i->Draw();
		}

		// Draw Enemies
		for (auto &j : m_enemies) {
			j->Draw();
		}

		// Debugging...
		//Debugging
		App::DrawLine(playerPos.x, playerPos.y, centerPos.x, centerPos.y, GameMath::Green.r, GameMath::Green.g, GameMath::Green.b);
	}

	virtual ~Level() {

		for (auto &i : m_bullets) {
			delete i;
		}

		for (auto &j : m_enemies) {
			delete j;
		}
	}
};
#endif