#ifndef SPIKE_H
#define SPIKE_H

#include "Enemy.h"

class Spike : public Enemy {

private:
	Vec2 m_stops[20];
	int m_currentStop;
public:

	Spike(Vec2 position, Vec2 sectionTop, Vec2 sectionBack);
	~Spike();
	void Update(float deltaTime);
	void Draw();
	void GetShot();
};
#endif