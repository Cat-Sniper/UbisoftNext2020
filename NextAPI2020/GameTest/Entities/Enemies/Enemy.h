#ifndef ENEMY_H
#define ENEMY_H
#include "Managers/Types.h"

class Enemy {



protected:
	
	Vec2 m_geometry[MAX_VERTS];
	Vec2 m_stops[NUM_STOPS];
	Vec2 m_position;
	Vec2 m_direction;
	
	int m_section[2];			// 0 = left, 1 = right
	int m_currentStop;
	int m_nVerts = MAX_VERTS;

	bool m_canShoot;
	bool m_isAlive;
	bool m_hurtOnTouch;
	bool m_canMove;

	float m_hitRadius;
	float m_scale;
	float m_angle;

	float m_moveDelay = 2500.0f;
	float m_adjustment;
	float m_timeSinceLastMove;
	float m_currentTime;

public:

	~Enemy(){};
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	bool IsAlive() { return m_isAlive; }
	void SetAlive(bool alive) { m_isAlive = alive; }
	void SetPosition(Vec2 position) { m_position = position; }
	Vec2 GetPosition() { return m_position; }

	Vec2* GetGeometry() { return m_geometry; }

	virtual void GetShot() = 0;
	float HitRadius() { return m_hitRadius; }
	void SetDirection(Vec2 direction) { m_direction = direction; }
	int GetLeft() { return m_section[0]; }
	int GetRight() { return m_section[1]; }
	const int VERTS() { return m_nVerts; }
	bool HurtOnTouch() { return m_hurtOnTouch; }

};
#endif