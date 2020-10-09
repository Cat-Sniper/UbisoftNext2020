#include "stdafx.h"
#include "Bullet.h"

#include "App/app.h"
#include "Managers/GameMath.h"

Bullet::Bullet(bool enemyBullet, Vec2 position, int left, int right)
{
	m_enemyBullet = enemyBullet;
	m_position = position;
	m_startPosition = position;
	m_lastScale = m_scale;

	m_angle = 90.0f;
	if (enemyBullet) {

		m_section[1] = left;
		m_section[0] = right;
	}
	else {

		m_section[0] = left;
		m_section[1] = right;
	}

	for (int i = 0; i < BULLET_VERTS; i++) {

		m_geometry[i].x += 3.0f;
		m_geometry[i].y += 3.0f;

		m_geometry[i].x *= 5.0f;
		m_geometry[i].y *= 5.0f;
	}
}

void Bullet::Draw()
{
	if (m_isAlive) {
		Vec2 startPos = m_geometry[0];

		for (int i = 1; i < BULLET_VERTS; i++) {

			Vec2 endPos = m_geometry[i];

			App::DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, GameMath::Red.r, GameMath::Red.g, GameMath::Red.b);
			startPos = endPos;

			if (i == BULLET_VERTS - 1) {
				endPos = m_geometry[0];
				App::DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, GameMath::Red.r, GameMath::Red.g, GameMath::Red.b);
			}
		}
	}
}

void Bullet::Update(float deltaTime)
{
	if (m_isAlive) {

		// Calculate position of player center
		Vec2 centroidPt;
		int xSum = 0, ySum = 0;

		for (int k = 0; k < BULLET_VERTS; k++) {
			xSum += m_geometry[k].x;
			ySum += m_geometry[k].y;
		}

		centroidPt.x = (float)xSum / BULLET_VERTS;
		centroidPt.y = (float)ySum / BULLET_VERTS;

		Vec2 newPos = m_position;
		newPos.x += m_direction.x * m_speed;
		newPos.y += m_direction.y * m_speed;

		float newDistance = GameMath::Distance(m_position, m_destination);
		m_scale = newDistance / m_distance;

		// m_distance / m_distance = 1
		// m_destinataion / m_distance = 0

		Vec2 t = { newPos.x - centroidPt.x, newPos.y - centroidPt.y };

		// Declare and initialize composite matrix to identity
		Matrix3x3 matComposite;
		GameMath::Matrix3x3SetIdentity(matComposite);

		GameMath::Scale2D(m_scale, m_scale, centroidPt, matComposite);
		GameMath::Translate2D(t.x, t.y, matComposite);

		// Apply composite matrix to bullet vertices
		GameMath::TransformVerts2D(BULLET_VERTS, m_geometry, matComposite);

		m_position = newPos;
		m_distance = newDistance;

		if (m_distance <= 10.0f) m_isAlive = false;
	}
	
}

void Bullet::SetDestination(Vec2 dest)
{
	m_destination = dest;
	m_distance = GameMath::Distance(m_startPosition, m_destination);

}
