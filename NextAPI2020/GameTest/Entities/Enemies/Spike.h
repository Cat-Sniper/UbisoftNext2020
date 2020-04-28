#ifndef SPIKE_H
#define SPIKE_H
#include "Enemy.h"

class Spike : public Enemy {




private:
	
public:

	Spike(Vec2 position, Vec2 sectionTop, Vec2 sectionBack, Vec2 section, float speedAdjustment);
	~Spike();
	void Update(float deltaTime);
	void Draw();
	void GetShot();
};
#endif