#ifndef CIRCLE_LEVEL_H
#define CIRCLE_LEVEL_H

#include "Entities/Level.h"

class CircleLevel : public Level {

private:
	
	
public:
	CircleLevel(Player* player);

	void Update(float deltaTime);
	Vec2 GetForground(int i) { return m_foregroundGeometry[i]; }
	Vec2 GetBackground(int i) { return m_backgroundGeometry[i]; }
	Vec2 GetSectionCenter();
	Vec2 GetSectionNormal();
	Vec2 GetPlayerCenter();

	void MoveLeft();
	void MoveRight();
	void TransformPlayer();
};
#endif
