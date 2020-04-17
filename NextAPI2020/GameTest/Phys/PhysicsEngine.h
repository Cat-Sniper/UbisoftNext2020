#pragma once
#ifndef PHYS_ENG_H
#define PHYS_ENG_H

#include "Collider.h"
#include "AABB.h"
#include "CircleCollider.h"

#include <vector>

class PhysicsEngine {
private:
	std::vector<Collider> colliders;

public:
	bool TestAABBOverlap(AABB *a, AABB *b);
	bool TestCircleOverlap(CircleCollider *a, CircleCollider *b);
	bool TestAABBCircleOverlap(AABB *a, CircleCollider *b);
	bool PointInRectangle(Vector2 Point, AABB *rect);
	bool IntersectCircle(CircleCollider *circle, Vector2 a, Vector2 b);
};
#endif

/*
	Keeps track of all colliders in the game and once every update
	it will check for collisions, resolving any before the game renders
	the frame.
*/