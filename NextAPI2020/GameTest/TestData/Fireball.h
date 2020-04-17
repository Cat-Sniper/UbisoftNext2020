/* Fireball.h - Simple test class for a moving fireball
 * Author: Michael Ward
 * Created: March 13, 2020
 * Edited: March 14, 2020
 */


#pragma once
#ifndef FIREBALL_H
#define FIREBALL_H

#include "Entity.h"
#include "../Phys/RigidBody.h"

class Fireball : public Entity {
private:
	float m_timeRemaining = 0.0F;
	float m_speed = 100;
	float m_angle;
	RigidBody* m_rigidbody;

public:
	Fireball(float timeAlive, float x, float y, float angle);
	~Fireball();
	void Update(float dt);
	void Draw();
};
#endif // !_FIREBALL_H
