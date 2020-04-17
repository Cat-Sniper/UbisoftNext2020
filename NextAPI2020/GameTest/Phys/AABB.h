#pragma once
#ifndef AABB_H
#define AABB_H
#include "Collider.h"

// Axis alligned bounding box collider
class AABB : public Collider {
private:
	Vector2 min;
	Vector2 max;

public:
	Vector2 GetMin() { return min; }
	Vector2 GetMax() { return max; }
	float GetWidth() { return (min.x + max.x) / 2; }
	float GetHeight(){ return (min.y + max.y) / 2; }
};

#endif