#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>

#include "Entities/Levels/Level.h"
#include "Entities/Levels/AllLevels.h"

class GameManager;
class Player;

class LevelManager {

	struct ColorScheme {
		Color level;
		Color player;
	};
private:

	int m_currentLevelIndex;
	int m_numLevels = 4;
	int m_completedLevels = 0;

	int m_numEnemies;

	Player *ptr_player;
	GameManager* ptr_gameManager;

	Level *m_currentLevel;

	int m_colorScheme = 0;
	ColorScheme m_colorschemes[5] = {
		{GameMath::Blue, GameMath::Yellow},
		{GameMath::Green, GameMath::Orange },
		{GameMath::Yellow, GameMath::Red },
		{GameMath::Orange, GameMath::Blue},
		{GameMath::Red, GameMath::Green}
	};
public:

	LevelManager(Player* player, GameManager* gameManager);
	void Update(float deltaTime);
	void Draw();

	void LoadLevel();
	Level* GetCurrentLevel() { return m_currentLevel; }
	int GetCurrentLevelNumber() { return m_completedLevels; }
	void ResetGame();
	~LevelManager();
};
#endif
