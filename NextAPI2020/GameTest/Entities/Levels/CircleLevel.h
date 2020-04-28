#ifndef CIRCLE_LEVEL_H
#define CIRCLE_LEVEL_H

#include "Level.h"
#include "Managers/Types.h"
#include "Entities/Player.h"

class CircleLevel : public Level {

public:

	CircleLevel(Player* player, GameManager* gameManager) : Level(player, gameManager){}
	void LoadLevel(Color level, Color player, int nEnemies)
	{
		m_loops = true;
		m_currentSection[0] = 13;
		m_currentSection[1] = 14;

		m_hasMoved = true;
		m_levelColor = level;
		m_playerColor = player;

		// Initialize Level Geometry
		m_foregroundGeometry[0] = { 14.0f,   0.0f }; m_foregroundGeometry[1] = { 13.0f,  -6.0f };
		m_foregroundGeometry[2] = { 10.0f, -10.0f };  m_foregroundGeometry[3] = { 5.0f, -13.0f };
		m_foregroundGeometry[4] = { 0.0f, -14.0f };  m_foregroundGeometry[5] = { -5.0f, -13.0f };
		m_foregroundGeometry[6] = { -10.0f, -10.0f };  m_foregroundGeometry[7] = { -13.0f,  -6.0f };
		m_foregroundGeometry[8] = { -14.0f,   0.0f };  m_foregroundGeometry[9] = { -13.0f,   6.0f };
		m_foregroundGeometry[10] = { -10.0f,  10.0f };  m_foregroundGeometry[11] = { -5.0f,  13.0f };
		m_foregroundGeometry[12] = { 0.0f,  14.0f };  m_foregroundGeometry[13] = { 5.0f,  13.0f };
		m_foregroundGeometry[14] = { 10.0f,  10.0f }; m_foregroundGeometry[15] = { 13.0f,   6.0f };


		m_backgroundGeometry[0] = { 3.0f,  -5.0f }; m_backgroundGeometry[1] = { 2.7f,  -6.2f };
		m_backgroundGeometry[2] = { 2.0f,  -7.0f }; m_backgroundGeometry[3] = { 1.2f,  -7.7f };
		m_backgroundGeometry[4] = { 0.0f,  -8.0f }; m_backgroundGeometry[5] = { -1.2f,  -7.7f };
		m_backgroundGeometry[6] = { -2.0f,  -7.0f }; m_backgroundGeometry[7] = { -2.7f,  -6.2f };
		m_backgroundGeometry[8] = { -3.0f,  -5.0f }; m_backgroundGeometry[9] = { -2.7f,  -3.8f };
		m_backgroundGeometry[10] = { -2.0f,  -3.0f }; m_backgroundGeometry[11] = { -1.2f,  -2.3f };
		m_backgroundGeometry[12] = { 0.0f,  -2.0f }; m_backgroundGeometry[13] = { 1.2f,  -2.3f };
		m_backgroundGeometry[14] = { 2.0f,  -3.0f }; m_backgroundGeometry[15] = { 2.7f,  -3.8f };

		// Scale geometry 
		for (int i = 0; i < LEVEL_VERTS; i++) {

			m_foregroundGeometry[i].x += 20.0f;
			m_foregroundGeometry[i].y += 16.0f;
			m_backgroundGeometry[i].x += 20.0f;
			m_backgroundGeometry[i].y += 14.0f;

			m_foregroundGeometry[i].x *= 25.0f;
			m_foregroundGeometry[i].y *= 25.0f;
			m_backgroundGeometry[i].x *= 25.0f;
			m_backgroundGeometry[i].y *= 25.0f;

		}

		m_enemySpawner->InitializeSpawner(16, nEnemies);
		ptr_player->SetColor(player);
		ptr_player->DoneLoading(true);

	}

};
#endif
