#include "stdafx.h"
#include "Player.h"

#include "App/app.h"
#include "Managers/GameMath.h"

Player::Player() {

	for (int i = 0; i < PLAYER_VERTS; i++) {

		m_geometry[i].x += 3.0f;
		m_geometry[i].y += 3.0f;

		m_geometry[i].x *= 25.0f;
		m_geometry[i].y *= 25.0f;
	}

	m_remainingLives = 3;
	m_isAlive = true;
}

void Player::Init()
{
	m_remainingLives = 3;
	m_remainingSupers = 1;
	m_isAlive = true;
}

void Player::Draw()
{
	if (m_isAlive && m_levelLoaded) {

		Vec2 startPos = m_geometry[0];

		for (int i = 1; i < PLAYER_VERTS; i++) {
			Vec2 endPos = m_geometry[i];

			App::DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, m_color.r, m_color.g, m_color.b);
			startPos = endPos;

			if (i == PLAYER_VERTS - 1) {

				endPos = m_geometry[0];
				App::DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, m_color.r, m_color.g, m_color.b);

			}
		}
	}
}

void Player::Update(float deltaTime)
{
	if (m_levelLoaded) {

		float elapsedTime = m_currentTime + deltaTime;

		if (!m_isAlive && elapsedTime - m_timeSinceDeath > m_respawnTime) m_isAlive = true;
		
		m_currentTime = elapsedTime;
	}
}

void Player::GetShot()
{
	m_remainingLives--;
	m_timeSinceDeath = m_currentTime;
	m_isAlive = false;
}




