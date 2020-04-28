#ifndef SQUARE_LEVEL_H
#define SQUARE_LEVEL_H


#include "Level.h"

class SquareLevel : public Level {

public:

	SquareLevel(Player* player, GameManager* gameManager) : Level(player, gameManager) {}

	void LoadLevel(Color level, Color player, int nEnemies) {


		// Init parameters
		m_loops = true;
		m_currentSection[0] = 13;
		m_currentSection[1] = 14;

		m_hasMoved = true;
		m_levelColor = level;
		m_playerColor = player;

		

		// Initialize Level Geometry
		m_foregroundGeometry[0] = { 13.0f,   0.0f }; m_foregroundGeometry[1] = { 13.0f,  -6.0f };
		m_foregroundGeometry[2] = { 13.0f, -13.0f };  m_foregroundGeometry[3] = { 6.0f, -13.0f };
		m_foregroundGeometry[4] = { 0.0f, -13.0f };  m_foregroundGeometry[5] = { -6.0f, -13.0f };
		m_foregroundGeometry[6] = { -13.0f, -13.0f };  m_foregroundGeometry[7] = { -13.0f,  -6.0f };
		m_foregroundGeometry[8] = { -13.0f,   0.0f };  m_foregroundGeometry[9] = { -13.0f,   6.0f };
		m_foregroundGeometry[10] = { -13.0f,  13.0f };  m_foregroundGeometry[11] = { -6.0f,  13.0f };
		m_foregroundGeometry[12] = { 0.0f,  13.0f };  m_foregroundGeometry[13] = { 6.0f,  13.0f };
		m_foregroundGeometry[14] = { 13.0f,  13.0f }; m_foregroundGeometry[15] = { 13.0f,   6.0f };


		m_backgroundGeometry[0] = { 5.0f,  -4.0f }; m_backgroundGeometry[1] = { 5.0f,  -6.0f };
		m_backgroundGeometry[2] = { 5.0f,  -9.0f }; m_backgroundGeometry[3] = { 2.0f,  -9.0f };
		m_backgroundGeometry[4] = { 0.0f,  -9.0f }; m_backgroundGeometry[5] = { -2.0f,  -9.0f };
		m_backgroundGeometry[6] = { -5.0f,  -9.0f }; m_backgroundGeometry[7] = { -5.0f,  -6.0f };
		m_backgroundGeometry[8] = { -5.0f,  -4.0f }; m_backgroundGeometry[9] = { -5.0f,  -2.0f };
		m_backgroundGeometry[10] = { -5.0f,  1.0f }; m_backgroundGeometry[11] = { -2.0f,  1.0f };
		m_backgroundGeometry[12] = { 0.0f,  1.0f }; m_backgroundGeometry[13] = { 2.0f,  1.0f };
		m_backgroundGeometry[14] = { 5.0f,  1.0f }; m_backgroundGeometry[15] = { 5.0f,  -2.0f };

		// Scale geometry 
		for (int i = 0; i < LEVEL_VERTS; i++) {

			m_foregroundGeometry[i].x += 20.0f;
			m_foregroundGeometry[i].y += 16.0f;
			m_backgroundGeometry[i].x += 40.0f;
			m_backgroundGeometry[i].y += 28.0f;

			m_foregroundGeometry[i].x *= 25.0f;
			m_foregroundGeometry[i].y *= 25.0f;
			m_backgroundGeometry[i].x *= 12.50f;
			m_backgroundGeometry[i].y *= 12.50f;

		}
		
		PopulateSectionLengths();
		m_enemySpawner->InitializeSpawner(16, nEnemies);
		ptr_player->SetColor(player);
		ptr_player->DoneLoading(true);

	}
};
#endif