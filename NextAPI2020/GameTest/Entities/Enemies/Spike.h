#ifndef SPIKE_H
#define SPIKE_H
#include "Enemy.h"

class Spike : public Enemy {


#define NUM_STOPS 15

private:
	Vec2 m_stops[NUM_STOPS];
	int m_currentStop;

	float m_moveDelay = 2500.0f;
	float m_adjustment;
	float m_timeSinceLastMove;
	float m_currentTime;
	bool m_canMove;

public:

	Spike(Vec2 position, Vec2 sectionTop, Vec2 sectionBack, Vec2 section, float speedAdjustment);
	~Spike();
	void Update(float deltaTime);
	void Draw();
	void GetShot();
};
#endif