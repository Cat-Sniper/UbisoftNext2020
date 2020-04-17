#include "stdafx.h"
#include "PhysicsEngine.h"

bool PhysicsEngine::TestAABBOverlap(AABB *a, AABB *b) {

	float d1x = b->GetMin().x - a->GetMax().x;
	float d1y = b->GetMin().y - a->GetMax().y;
	float d2x = a->GetMin().x - b->GetMax().x;
	float d2y = a->GetMin().y - b->GetMax().y;

	if (d1x > 0.0f || d1y > 0.0f) return false;
	if (d2x > 0.0f || d2y > 0.0f) return false;

	return true;
}

bool PhysicsEngine::TestCircleOverlap(CircleCollider * a, CircleCollider * b) {
	
	float x = a->GetCentreX() - b->GetCentreX();
	float y = a->GetCentreY() - b->GetCentreY();
	float centreDistanceSq = x * x + y * y;
	float radius = a->GetRadius() + b->GetRadius();
	float radiusSq = radius * radius;
	return centreDistanceSq <= radiusSq;

}

bool PhysicsEngine::TestAABBCircleOverlap(AABB * a, CircleCollider * b) {
	
	float testX = b->GetCentreX();
	float testY = b->GetCentreY();
	
	// Determine closest point
	if (b->GetCentreX() < a->GetMin().x)		// left
		testX = a->GetMin().x;
	else if (b->GetCentreX() > a->GetMax().x)	// right
		testX = a->GetMax().x;
	
	if (b->GetCentreY() < a->GetMin().y)		// top
		testY = a->GetMin().y;
	else if (b->GetCentreY() > a->GetMax().y)	// bottom
		testY = a->GetMax().y;

	float distX = b->GetCentreX() - testX;
	float distY = b->GetCentreY() - testY;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= b->GetRadius()) return true;
	return false;
}

bool PhysicsEngine::PointInRectangle(Vector2 Point, AABB * rect) {

	if (Point.x >= rect->GetMin().x && Point.x <= rect->GetMax().x &&
		Point.y >= rect->GetMin().y && Point.y <= rect->GetMax().y)
		return true;
	else 
		return false;
}

bool PhysicsEngine::IntersectCircle(CircleCollider *circle, Vector2 a, Vector2 b) {
	return false;


}
