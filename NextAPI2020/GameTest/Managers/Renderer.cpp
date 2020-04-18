#include "stdafx.h"
#include "Renderer.h"

#include <string>
#include "App/app.h"
#include "GameMath.h"
#include "LevelManager.h"
#include "Entities/Player.h"

Renderer::Renderer(GameManager *gameManager, LevelManager *levelManager, Player* player) 
{
	m_gameManager = gameManager;
	m_levelManager = levelManager;
	m_player = player;
	m_levelColor = GameMath::Blue;
	m_hasMoved = true;
}

void Renderer::DrawLevel()
{

	int numVerts = m_levelManager->GetCurrentLevel()->GetVerts();
	bool levelLoop = m_levelManager->GetCurrentLevel()->DoesLoop();

	// Draw foreground
	Vec2 startPosFor = m_levelManager->GetCurrentLevel()->GetForground(0);
	Vec2 startPosBack = m_levelManager->GetCurrentLevel()->GetBackground(0);

	for (int i = 1; i < numVerts; i++) {
		
		Vec2 endPosFor = m_levelManager->GetCurrentLevel()->GetForground(i);
		Vec2 endPosBack = m_levelManager->GetCurrentLevel()->GetBackground(i);

		// Draw lines: 
		App::DrawLine(startPosFor.x, startPosFor.y, endPosFor.x, endPosFor.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);			// forground
		App::DrawLine(startPosBack.x, startPosBack.y, endPosBack.x, endPosBack.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);		// background
		App::DrawLine(startPosFor.x, startPosFor.y, startPosBack.x, startPosBack.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);		// connect back to for

		startPosFor = endPosFor;
		startPosBack = endPosBack;

		// Final position
		if (i == numVerts - 1) {

			App::DrawLine(startPosFor.x, startPosFor.y, startPosBack.x, startPosBack.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);	// connect back to for
			
			// Connect looped levels
			if (levelLoop) {

				endPosFor = m_levelManager->GetCurrentLevel()->GetForground(0);
				endPosBack = m_levelManager->GetCurrentLevel()->GetBackground(0);

				App::DrawLine(startPosFor.x, startPosFor.y, endPosFor.x, endPosFor.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);
				App::DrawLine(startPosBack.x, startPosBack.y, endPosBack.x, endPosBack.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);
			}
		}
	}
}

void Renderer::DrawPlayer() 
{	

	Vec2 startPos = m_player->GetGeometry(0);

	for (int i = 1; i < Player::VERTS; i++) {
		Vec2 endPos = m_player->GetGeometry(i);

		App::DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, GameMath::Yellow.r, GameMath::Yellow.g, GameMath::Yellow.b);
		startPos = endPos;

		if (i == Player::VERTS - 1) {

			endPos = m_player->GetGeometry(0);
			App::DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, GameMath::Yellow.r, GameMath::Yellow.g, GameMath::Yellow.b);

		}
	}
}

Renderer::~Renderer()
{
	
}

void Renderer::TransformPlayer() {
	
	// Player Geometry information
	int nVerts = Player::VERTS;
	Vec2 *verts = m_player->GetGeometry();

	// Calculate position of player center
	Vec2 centroidPt;
	int xSum = 0, ySum = 0;

	for (int k = 0; k < nVerts; k++) {
		xSum += verts[k].x;
		ySum += verts[k].y;
	}

	centroidPt.x = (float)xSum / (float)nVerts;
	centroidPt.y = (float)ySum / (float)nVerts;
	
	// Set Geometric tranformation parameters
	Vec2 pivotPt = centroidPt;
	Vec2 fixedPt = centroidPt;
	Vec2 playerPos = m_levelManager->GetCurrentLevel()->GetPlayerCenter();
	Vec2 centerPos = m_levelManager->GetCurrentLevel()->GetSectionCenter();
	Vec2 t = { playerPos.x - centroidPt.x, playerPos.y - centroidPt.y};								// Translation
	Vec2 normal = m_levelManager->GetCurrentLevel()->GetSectionNormal();
	float angle = atan2(-normal.y, -normal.x);				// Get angle defined by the line between the two points and the horizontal axis

	// Declare and initialize composite matrix to identity
	Matrix3x3 matComposite;
	GameMath::Matrix3x3SetIdentity(matComposite);
	
	// Construct composite matrix for transformation sequence
	GameMath::Scale2D(m_player->GetScale().x, m_player->GetScale().y, fixedPt, matComposite);
	if (m_hasMoved) {
		GameMath::Rotate2D(pivotPt, angle, matComposite);
		GameMath::Translate2D(t.x, t.y, matComposite);
		m_hasMoved = false;
	}
	

	// Apply composite matrix to player vertices
	GameMath::TransformVerts2D(nVerts, verts, matComposite);
	
	// Debugging...
	App::DrawLine(playerPos.x, playerPos.y, centerPos.x, centerPos.y, GameMath::Red.r, GameMath::Red.g, GameMath::Red.b);

}
