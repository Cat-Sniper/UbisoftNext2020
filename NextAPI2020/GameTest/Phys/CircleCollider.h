#pragma once
#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H
#include "Collider.h"
class CircleCollider : public Collider {

private :
	float centreX;
	float centreY;
	float radius;

public:
	float GetCentreX() { return centreX; }
	float GetCentreY() { return centreY; }
	float GetRadius() { return radius; }
};
#endif