#ifndef ENEMY_H
#define ENEMY_H
#include "Managers/Types.h"

class Enemy {
protected:
	const int m_nVerts = 16;
	Vec2 m_geometry[16];
	Vec2 m_position;
	Vec2 m_direction;
	float m_scale;
	float m_angle;
	int m_section[2];
	bool m_canShoot;
	bool m_isAlive;

public:

	~Enemy(){};
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	bool IsAlive() { return m_isAlive; }
	void SetPosition(Vec2 position) { m_position = position; }
	Vec2 GetPosition() { return m_position; }

	Vec2* GetGeometry() { return m_geometry; }

	void SetDirection(Vec2 direction) { m_direction = direction; }
	const int VERTS() { return m_nVerts; }
};
#endif