#ifndef CIRCLE_LEVEL_H
#define CIRCLE_LEVEL_H

#include "Level.h"


class Spike;

class CircleLevel : public Level {

private:

	Vec2 GetSectionBack(int left, int right);
	Vec2 GetSectionNormal(int left, int right);
	Vec2 GetBulletDirection(int left, int right);
	
	void TransformPlayer(float deltaTime);
	void TransformBullet(Bullet* bullet);
	void TransformEnemy(Enemy* enemy);

public:
	CircleLevel(Player* player);
	~CircleLevel();
	void Update(float deltaTime);
	void SpawnBullet(bool enemyBullet, Vec2 position);
	void SpawnEnemy(EnemyType enemy, Vec2 position);
	void MoveLeft();
	void MoveRight();
	Vec2 GetSectionTop(int left, int right);
	Vec2 GetSectionTop();

};
#endif
