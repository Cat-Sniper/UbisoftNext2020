#ifndef FLIPPER_H
#define FLIPPER_H
#include "Enemy.h"

class Flipper : public Enemy {

private:

public:
	Flipper(Vec2 position, Vec2 sectionTop, Vec2 sectionBack, Vec2 section, float adjustment);
	~Flipper();
	void Update(float deltaTime);
	void Draw();
	void GetShot();
};

#endif