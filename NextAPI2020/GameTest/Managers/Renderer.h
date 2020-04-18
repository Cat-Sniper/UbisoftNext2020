#ifndef RENDERER_H
#define RENDERER_H

// Forward Declaration
class GameManager;
class LevelManager;
class Player;


class Renderer {

private:

	GameManager* m_gameManager;
	LevelManager* m_levelManager;
	Player* m_player;
	bool m_hasMoved;
	Color m_levelColor;
	
	void TransformPlayer();

public:
	Renderer(GameManager *gameManager, LevelManager *levelManager, Player *player);
	void DrawLevel();
	void DrawPlayer();
	~Renderer();
};
#endif