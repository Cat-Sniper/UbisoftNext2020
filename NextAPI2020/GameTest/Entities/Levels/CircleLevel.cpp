#include "stdafx.h"
#include "CircleLevel.h"

#include "Entities/Player.h"
#include "Managers/GameMath.h"
#include "App/app.h"

CircleLevel::CircleLevel(Player* player) 

{
	ptr_player = player;
	m_loops = true;
	m_hasMoved = true;
	m_currentSection[0] = 0;
	m_currentSection[1] = 1;
	

	m_foregroundGeometry[0]	= { 14.0f,   0.0f }; m_foregroundGeometry[1]  = { 13.0f,  -6.0f };
	m_foregroundGeometry[2]	= { 10.0f, -10.0f};  m_foregroundGeometry[3]  = {  5.0f, -13.0f};
	m_foregroundGeometry[4]	= {  0.0f, -14.0f};  m_foregroundGeometry[5]  = { -5.0f, -13.0f}; 
	m_foregroundGeometry[6]	= {-10.0f, -10.0f};  m_foregroundGeometry[7]  = {-13.0f,  -6.0f};
	m_foregroundGeometry[8]	= {-14.0f,   0.0f};  m_foregroundGeometry[9]  = {-13.0f,   6.0f}; 
	m_foregroundGeometry[10] = {-10.0f,  10.0f};  m_foregroundGeometry[11] = { -5.0f,  13.0f};
	m_foregroundGeometry[12] = {  0.0f,  14.0f};  m_foregroundGeometry[13] = {  5.0f,  13.0f}; 
	m_foregroundGeometry[14] = { 10.0f,  10.0f }; m_foregroundGeometry[15] = { 13.0f,   6.0f };
	

	m_backgroundGeometry[0]	= {  3.0f,  -5.0f }; m_backgroundGeometry[1]  = { 2.7f,  -6.2f };
	m_backgroundGeometry[2]	= {  2.0f,  -7.0f }; m_backgroundGeometry[3]  = { 1.2f,  -7.7f };
	m_backgroundGeometry[4]	= {  0.0f,  -8.0f }; m_backgroundGeometry[5]  = {-1.2f,  -7.7f };
	m_backgroundGeometry[6]	= { -2.0f,  -7.0f }; m_backgroundGeometry[7]  = {-2.7f,  -6.2f };
	m_backgroundGeometry[8]	= { -3.0f,  -5.0f }; m_backgroundGeometry[9]  = {-2.7f,  -3.8f };
	m_backgroundGeometry[10] = { -2.0f,  -3.0f }; m_backgroundGeometry[11] = {-1.2f,  -2.3f };
	m_backgroundGeometry[12] = {  0.0f,  -2.0f }; m_backgroundGeometry[13] = { 1.2f,  -2.3f };
	m_backgroundGeometry[14] = {  2.0f,  -3.0f }; m_backgroundGeometry[15] = { 2.7f,  -3.8f };

	for (int i = 0; i < m_nVerts; i++) {
		
		m_foregroundGeometry[i].x += 20.0f;
		m_foregroundGeometry[i].y += 16.0f;
		m_backgroundGeometry[i].x += 20.0f;
		m_backgroundGeometry[i].y += 16.0f;

		m_foregroundGeometry[i].x *= 25.0f;
		m_foregroundGeometry[i].y *= 25.0f;
		m_backgroundGeometry[i].x *= 25.0f;
		m_backgroundGeometry[i].y *= 25.0f;
		
	}
}

void CircleLevel::Update(float deltaTime) {
	TransformPlayer();
}
// Use midpoint formula on the background geometry of the current section
Vec2 CircleLevel::GetSectionCenter()
{
	return { (m_backgroundGeometry[m_currentSection[0]].x + m_backgroundGeometry[m_currentSection[1]].x) / 2,
		    (m_backgroundGeometry[m_currentSection[0]].y + m_backgroundGeometry[m_currentSection[1]].y) / 2 };

}

Vec2 CircleLevel::GetSectionNormal()
{
	return { m_foregroundGeometry[m_currentSection[1]].x - m_foregroundGeometry[m_currentSection[0]].x,
		    m_foregroundGeometry[m_currentSection[1]].y - m_foregroundGeometry[m_currentSection[0]].y };
}

Vec2 CircleLevel::GetPlayerCenter() {
	return { (m_foregroundGeometry[m_currentSection[0]].x + m_foregroundGeometry[m_currentSection[1]].x) / 2,
		    (m_foregroundGeometry[m_currentSection[0]].y + m_foregroundGeometry[m_currentSection[1]].y) / 2 };
}

void CircleLevel::MoveRight() {

		
	if (m_currentSection[1] < m_nVerts - 1) {

		m_currentSection[0]++;
		m_currentSection[1]++;
		m_hasMoved = true;

	} else {

		if (m_loops) {

			m_currentSection[0] = m_nVerts - 1;
			m_currentSection[1] = 0;
			m_hasMoved = true;

		}
	}
}

void CircleLevel::MoveLeft() {


	if (m_currentSection[0] > 0) {

		m_currentSection[0]--;
		m_currentSection[1]--;
		m_hasMoved = true;

	} else {

		if (m_loops) {

			m_currentSection[0] = m_nVerts - 1;
			m_currentSection[1] = 0;
			m_hasMoved = true;

		}
	}
}

void CircleLevel::TransformPlayer() {

	// Player Geometry information
	int nVerts = Player::VERTS;
	Vec2 *verts = ptr_player->GetGeometry();

	// Calculate position of player center
	Vec2 centroidPt;
	float xSum = 0, ySum = 0;

	for (int k = 0; k < nVerts; k++) {
		xSum += verts[k].x;
		ySum += verts[k].y;
	}

	centroidPt.x = xSum / nVerts;
	centroidPt.y = ySum / nVerts;

	// Set Geometric tranformation parameters
	Vec2 pivotPt = centroidPt;
	Vec2 fixedPt = centroidPt;
	Vec2 playerPos = GetPlayerCenter();
	Vec2 centerPos = GetSectionCenter();
	Vec2 t = { playerPos.x - centroidPt.x, playerPos.y - centroidPt.y };								// Translation
	Vec2 normal = GetSectionNormal();
	float angle = atan2(-normal.y, -normal.x);				// Get angle defined by the line between the two points and the horizontal axis

	// Declare and initialize composite matrix to identity
	Matrix3x3 matComposite;
	GameMath::Matrix3x3SetIdentity(matComposite);

	// Construct composite matrix for transformation sequence
	if (m_hasMoved) {
		GameMath::Scale2D(ptr_player->GetScale().x, ptr_player->GetScale().y, fixedPt, matComposite);
		GameMath::Rotate2D(pivotPt, angle, matComposite);
		GameMath::Translate2D(t.x, t.y, matComposite);
		m_hasMoved = false;
	}


	// Apply composite matrix to player vertices
	GameMath::TransformVerts2D(nVerts, verts, matComposite);

	// Debugging...
	App::DrawLine(playerPos.x, playerPos.y, centerPos.x, centerPos.y, GameMath::Red.r, GameMath::Red.g, GameMath::Red.b);

}