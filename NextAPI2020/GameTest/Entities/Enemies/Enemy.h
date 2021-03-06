#ifndef ENEMY_H
#define ENEMY_H
#include "Managers/Types.h"

class Enemy {
protected:
	const int m_nVerts = 16;
	Vec2 m_geometry[16];
	Vec2 m_position;
	Vec2 m_direction;
	float m_hitRadius;
	float m_scale;
	float m_angle;
	int m_section[2];
	bool m_canShoot;
	bool m_isAlive;
	bool m_hurtOnTouch;

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