#pragma once
#ifndef TRIANGLE_LEVEL_H
#define TRIANGLE_LEVEL_H
#include "Level.h"
#include "Managers/Types.h"
#include "Entities/Player.h"

class TriangleLevel : public Level {

public:

	TriangleLevel(Player* player, GameManager* gameManager) : Level(player, gameManager) {}
	void LoadLevel(Color level, Color player, int nEnemies)
	{
		m_loops = true;
		m_currentSection[0] = 2;
		m_currentSection[1] = 3;

		m_hasMoved = true;
		m_levelColor = level;
		m_playerColor = player;

		// Initialize Level Geometry
		m_foregroundGeometry[0] = { 13, -13 }; m_foregroundGeometry[1] = { 8, -13 };
		m_foregroundGeometry[2] = { 4, -13 };  m_foregroundGeometry[3] = { 0, -13 };
		m_foregroundGeometry[4] = { -4, -13 };  m_foregroundGeometry[5] = { -8, -13 };
		m_foregroundGeometry[6] = { -13,-13 };  m_foregroundGeometry[7] = { -11, -10 };
		m_foregroundGeometry[8] = { -8, -3 };  m_foregroundGeometry[9] = { -5, 2 };
		m_foregroundGeometry[10] = { -3, 8 };  m_foregroundGeometry[11] = { 0, 13 };
		m_foregroundGeometry[12] = { 3, 8 };  m_foregroundGeometry[13] = { 5,2 };
		m_foregroundGeometry[14] = { 8,-3 }; m_foregroundGeometry[15] = { 11, -10 };


		m_backgroundGeometry[0] = { 3, -6 };	m_backgroundGeometry[1] = { 2, -6 };
		m_backgroundGeometry[2] = { 1, -6 };	m_backgroundGeometry[3] = { 0, -6 };
		m_backgroundGeometry[4] = { -1, -6 };	m_backgroundGeometry[5] = { -2, -6 };
		m_backgroundGeometry[6] = { -3,-6 };	m_backgroundGeometry[7] = { -2.5, -5 };
		m_backgroundGeometry[8] = { -2, -4 };	m_backgroundGeometry[9] = { -1.5, -3 };
		m_backgroundGeometry[10] = { -1, -2 };	m_backgroundGeometry[11] = { 0, 0 };

		m_backgroundGeometry[12] = { 1, -2 };	m_backgroundGeometry[13] = { 1.5, -3 };
		m_backgroundGeometry[14] = { 2, -4 };     m_backgroundGeometry[15] = { 2.5, -5 };

		// Scale geometry 
		for (int i = 0; i < LEVEL_VERTS; i++) {

			m_foregroundGeometry[i].x += 17;
			m_foregroundGeometry[i].y += 16;
			m_backgroundGeometry[i].x += 16;
			m_backgroundGeometry[i].y += 16;

			m_foregroundGeometry[i].x *= 25;
			m_foregroundGeometry[i].y *= 25;
			m_backgroundGeometry[i].x *= 24;
			m_backgroundGeometry[i].y *= 24;

		}

		PopulateSectionLengths();
		m_enemySpawner->InitializeSpawner(16, nEnemies);
		ptr_player->SetColor(player);
		ptr_player->DoneLoading(true);

	}

};
#endif