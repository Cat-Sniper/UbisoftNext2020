#include "stdafx.h"
#include "Player.h"

Player::Player() {

	for (int i = 0; i < GEOMETRY_VERTS; i++) {

		m_geometry[i].x += 3.0f;
		m_geometry[i].y += 3.0f;

		m_geometry[i].x *= 25.0f;
		m_geometry[i].y *= 25.0f;
	}
}

Vec2 * Player::GetGeometry()
{
	Vec2 copy[GEOMETRY_VERTS];

	for (int i = 0; i < VERTS; i++) {
		copy[i].x = m_geometry[i].x;
		copy[i].y = m_geometry[i].y;
	}

	return copy;
}




