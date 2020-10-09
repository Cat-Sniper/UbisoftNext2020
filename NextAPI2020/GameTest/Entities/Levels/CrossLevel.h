#ifndef CROSS_LEVEL_H
#define CROSS_LEVEL_H
#include "Level.h"
#include "Managers/Types.h"
#include "Entities/Player.h"

class CrossLevel : public Level {

public:

	CrossLevel(Player* player, GameManager* gameManager) : Level(player, gameManager) {}
	void LoadLevel(Color level, Color player, int nEnemies)
	{
		m_loops = true;
		m_currentSection[0] = 5;
		m_currentSection[1] = 6;

		m_hasMoved = true;
		m_levelColor = level;
		m_playerColor = player;

		// Initialize Level Geometry
		m_foregroundGeometry[0] = { 13, -2 }; m_foregroundGeometry[1] = { 7, -3 };
		m_foregroundGeometry[2] = { 3, -7 };  m_foregroundGeometry[3] = { 2, -13 };
		m_foregroundGeometry[4] = { -2, -13 };  m_foregroundGeometry[5] = { -3, -7 };
		m_foregroundGeometry[6] = { -7,-3 };  m_foregroundGeometry[7] = { -13, -2 };
		m_foregroundGeometry[8] = { -13, 2 };  m_foregroundGeometry[9] = { -7, 3 };
		m_foregroundGeometry[10] = { -3, 7 };  m_foregroundGeometry[11] = { -2, 13 };
		m_foregroundGeometry[12] = { 2, 13 };  m_foregroundGeometry[13] = { 3,7 };
		m_foregroundGeometry[14] = { 7,3 }; m_foregroundGeometry[15] = { 13, 2 };


		m_backgroundGeometry[0] = { 13, -2 };	m_backgroundGeometry[1] = { 7, -3 };
		m_backgroundGeometry[2] = { 3, -7 };	m_backgroundGeometry[3] = { 2, -13 };
		m_backgroundGeometry[4] = { -2, -13 };	m_backgroundGeometry[5] = { -3, -7 };
		m_backgroundGeometry[6] = { -7,-3 };	m_backgroundGeometry[7] = { -13, -2 };
		m_backgroundGeometry[8] = { -13, 2 };	m_backgroundGeometry[9] = { -7, 3 };
		m_backgroundGeometry[10] = { -3, 7 };	m_backgroundGeometry[11] = { -2, 13 };
		m_backgroundGeometry[12] = { 2, 13 };	m_backgroundGeometry[13] = { 3,7 };
		m_backgroundGeometry[14] = { 7,3 };     m_backgroundGeometry[15] = { 13, 2 };

		// Scale geometry 
		for (int i = 0; i < LEVEL_VERTS; i++) {

			m_foregroundGeometry[i].x += 20.0f;
			m_foregroundGeometry[i].y += 14.0f;
			m_backgroundGeometry[i].x += 80.0f;
			m_backgroundGeometry[i].y += 64.0f;

			m_foregroundGeometry[i].x *= 28.0f;
			m_foregroundGeometry[i].y *= 28.0f;
			m_backgroundGeometry[i].x *= 6.25f;
			m_backgroundGeometry[i].y *= 6.0f;

		}

		PopulateSectionLengths();
		m_enemySpawner->InitializeSpawner(16, nEnemies);
		ptr_player->SetColor(player);
		ptr_player->DoneLoading(true);

	}

};
#endif