#include "stdafx.h"
#include "Spike.h"

#include "App/app.h"
#include "Managers/GameMath.h"

Spike::Spike(Vec2 position)
{
	m_isAlive = true;
	m_position = position;

	// Initialize Geometry
	m_geometry[0]  = { 3, 0}; m_geometry[1]  = { 1.5, 0.5}; m_geometry[2]  = { 2,-2};  m_geometry[3]  = { 0.5, -1.5};
	m_geometry[4]  = { 0,-3}; m_geometry[5]  = {-0.5,-1.5}; m_geometry[6]  = {-2,-2};  m_geometry[7]  = {-1.5, -0.5};
	m_geometry[8]  = {-3, 0}; m_geometry[9]  = {-1.5, 0.5}; m_geometry[10] = {-2, 2};  m_geometry[11] = {-0.5,  1.5};
	m_geometry[12] = { 0, 3}; m_geometry[13] = { 0.5, 1.5}; m_geometry[14] = { 2, 2};  m_geometry[15] = { 1.5,  0.5};

	for (int i = 0; i < m_nVerts; i++) {
		m_geometry[i].x += 3;
		m_geometry[i].y += 3;
	}
}

Spike::~Spike()
{
}

void Spike::Update(float deltaTime)
{

}

void Spike::Draw()
{
	if (m_isAlive) {
		Vec2 startPos = m_geometry[0];

		for (int i = 1; i < m_nVerts; i++) {

			Vec2 endPos = m_geometry[i];

			App::DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, GameMath::Red.r, GameMath::Red.g, GameMath::Red.b);
			startPos = endPos;

			if (i == m_nVerts - 1) {
				endPos = m_geometry[0];
				App::DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, GameMath::Red.r, GameMath::Red.g, GameMath::Red.b);
			}
		}
	}
}
