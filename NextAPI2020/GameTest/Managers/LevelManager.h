#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>

#include "Entities/Levels/Level.h"
#include "Entities/Levels/AllLevels.h"
#include "Entities/Player.h"
#include "Entities/Bullet.h"


class LevelManager {

private:
	Player *m_player;
	Level *m_currentLevel;
	Color m_levelColor;

public:

	LevelManager(Player* player);
	void Update(float deltaTime);
	void Draw();

	Level* GetCurrentLevel() { return m_currentLevel; }
	~LevelManager();
};
#endif
