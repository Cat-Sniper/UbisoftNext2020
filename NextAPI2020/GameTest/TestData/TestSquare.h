#pragma once
#ifndef TESTSQUARE_H
#define TESTSQUARE_H

#include "Entity.h"
#include "../Phys/RigidBody.h"

class TestSquare : public Entity {


private:
	RigidBody* m_rigidbody;
public:
	TestSquare(float x, float y, float angle);
	~TestSquare();
	void Draw();
	void Update(float dt);


};
#endif
