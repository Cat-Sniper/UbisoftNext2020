#include "stdafx.h"
#include "Spike.h"

#include "App/app.h"
#include "Managers/GameMath.h"

Spike::Spike(Vec2 position, Vec2 sectionTop, Vec2 sectionBack)
{
	m_isAlive = true;
	m_position = position;
	
	float lengthOfSection = GameMath::Distance(sectionTop, sectionBack);
	float currentLength = GameMath::Distance(position, sectionBack);
	Vec2 Direction = GameMath::NormalizeDirection(sectionTop, sectionBack);

	m_currentStop = currentLength * 19 / lengthOfSection;

	// Populate Vector stops
	for (int i = 0; i < 20; i++) {
		currentLength = lengthOfSection * i / 19;
		Vec2 stopPosition = { sectionTop.x + Direction.x * currentLength,
						  sectionTop.y + Direction.y * currentLength };
		m_stops[19 - i] = stopPosition;
	}

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
	if (m_isAlive) {

		// Calculate position of player center
		Vec2 centroidPt;
		int xSum = 0, ySum = 0;

		for (int k = 0; k < m_nVerts; k++) {
			xSum += m_geometry[k].x;
			ySum += m_geometry[k].y;
		}

		centroidPt.x = (float)xSum / m_nVerts;
		centroidPt.y = (float)ySum / m_nVerts;

		Vec2 newPos = m_position;

		Vec2 t = { newPos.x - centroidPt.x, newPos.y - centroidPt.y };

		// Declare and initialize composite matrix to identity
		Matrix3x3 matComposite;
		GameMath::Matrix3x3SetIdentity(matComposite);

		GameMath::Translate2D(t.x, t.y, matComposite);

		// Apply composite matrix to bullet vertices
		GameMath::TransformVerts2D(m_nVerts, m_geometry, matComposite);

	}
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

		App::DrawLine(m_stops[m_currentStop].x, m_stops[m_currentStop].y, m_stops[0].x, m_stops[0].y, GameMath::Orange.r, GameMath::Orange.g, GameMath::Orange.b);
	}
}

void Spike::GetShot()
{
	m_currentStop--;
	
	if (m_currentStop == 0) {
		m_isAlive = false;
	}

	else {
		m_position = m_stops[m_currentStop];
	}
}
