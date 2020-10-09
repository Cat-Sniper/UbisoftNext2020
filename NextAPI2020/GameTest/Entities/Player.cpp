#include "stdafx.h"
#include "Player.h"

#include "App/app.h"
#include "Managers/GameMath.h"

Player::Player() {

	for (int i = 0; i < GEOMETRY_VERTS; i++) {

		m_geometry[i].x += 3.0f;
		m_geometry[i].y += 3.0f;

		m_geometry[i].x *= 25.0f;
		m_geometry[i].y *= 25.0f;
	}
}

void Player::Draw()
{
	Vec2 startPos = m_geometry[0];

	for (int i = 1; i < GEOMETRY_VERTS; i++) {
		Vec2 endPos = m_geometry[i];

		App::DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, GameMath::Yellow.r, GameMath::Yellow.g, GameMath::Yellow.b);
		startPos = endPos;

		if (i == GEOMETRY_VERTS - 1) {

			endPos = m_geometry[0];
			App::DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, GameMath::Yellow.r, GameMath::Yellow.g, GameMath::Yellow.b);

		}
	}
}




