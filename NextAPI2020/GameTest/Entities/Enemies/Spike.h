#ifndef SPIKE_H
#define SPIKE_H

#include "Enemy.h"

class Spike : public Enemy {

private:
	Vec2 m_stops[10];
public:

	Spike(Vec2 position);
	~Spike();
	void Update(float deltaTime);
	void Draw();

};
#endif