#include "stdafx.h"
#include "Level.h"

#include "App/app.h"
#include "Entities/Enemies/AllEnemies.h"
#include "Entities/Enemies/Enemy.h"
#include "Entities/Player.h"
#include "Entities/Bullet.h"
#include "Managers/GameManager.h"


// Use midpoint formula on the background geometry of the specified section
Vec2 Level::GetSectionBack(int left, int right)
{
	if (right == 16) right = 0;
	return { (m_backgroundGeometry[left].x + m_backgroundGeometry[right].x) / 2,
		    (m_backgroundGeometry[left].y + m_backgroundGeometry[right].y) / 2 };
}

// Use midpoint formula on the foreground geometry of the specified section
Vec2 Level::GetSectionTop(int left, int right)
{
	if (right == 16) right = 0;
	return { (m_foregroundGeometry[left].x + m_foregroundGeometry[right].x) / 2,
		    (m_foregroundGeometry[left].y + m_foregroundGeometry[right].y) / 2 };
}

// Get the top center of current section
Vec2 Level::GetSectionTop()
{
	return GetSectionTop(GetSectionLeft(), GetSectionRight());
}

void Level::IncreaseDifficulty()
{
	m_speedAdjustment += 100.0f;
}


// Normalize direction of specified section:
Vec2 Level::GetSectionNormal(int left, int right)
{
	Vec2 back = GetSectionBack(left, right);
	Vec2 front = GetSectionTop(left, right);

	return GameMath::NormalizeDirection(front, back);
}


// Handle player update
void Level::TransformPlayer(float deltaTime)
{
	// Player Geometry information
	int nVerts = Player::VERTS;
	Vec2* verts = ptr_player->GetGeometry();

	float widthOfSection = GameMath::Distance(m_foregroundGeometry[m_currentSection[0]], m_foregroundGeometry[m_currentSection[1]]);
	float widthOfPlayer = GameMath::Distance(verts[1], verts[7]);
	float ratio = widthOfPlayer / widthOfSection;

	if (ratio < 1.0f) ptr_player->SetScale(1.1f);
	else if (ratio > 1.0f) ptr_player->SetScale(0.9f);


	// Calculate position of player center
	Vec2 centroidPt;
	int xSum = 0, ySum = 0;

	for (int k = 0; k < nVerts; k++) {
		xSum += verts[k].x;
		ySum += verts[k].y;
	}

	centroidPt.x = (float)xSum / nVerts;
	centroidPt.y = (float)ySum / nVerts;

	// Set Geometric tranformation parameters
	Vec2 pivotPt = centroidPt;
	Vec2 fixedPt = centroidPt;
	playerPos = GetSectionTop(m_currentSection[0], m_currentSection[1]);
	centerPos = GetSectionBack(m_currentSection[0], m_currentSection[1]);
	Vec2 t = { playerPos.x - centroidPt.x, playerPos.y - centroidPt.y };								// Translation
	Vec2 normal = GameMath::NormalizeDirection(m_foregroundGeometry[GetSectionLeft()], m_foregroundGeometry[GetSectionRight()]);

	// Animate the player a bit
	float fuzz = -0.01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.02)));

	float desiredAngle = atan2(-normal.y, -normal.x); // Get angle defined as a surface normal by the line between the two points (-normal.x to compensate for 90 degree rotation of model)
	float angle = desiredAngle - ptr_player->GetAngle();

	// Declare and initialize composite matrix to identity
	Matrix3x3 matComposite;
	GameMath::Matrix3x3SetIdentity(matComposite);

	// Construct composite matrix for transformation sequence
	GameMath::Scale2D(ptr_player->GetScale() + fuzz, ptr_player->GetScale() + fuzz, fixedPt, matComposite);
	GameMath::Rotate2D(pivotPt, angle, matComposite);
	GameMath::Translate2D(t.x, t.y, matComposite);

	// Apply composite matrix to player vertices
	GameMath::TransformVerts2D(nVerts, verts, matComposite);

	//ptr_player->SetAngle(atan2(matComposite[1][2], -matComposite[2][2]));
	ptr_player->SetAngle(desiredAngle);
	ptr_player->SetPosition(centroidPt);
	ptr_player->SetScale(1.0f);
	m_hasMoved = false;
}

void Level::TransformBullet(Bullet * bullet)
{
	// Bullet Geometry information
	int nVerts = Bullet::VERTS;
	Vec2* verts = bullet->GetGeometry();

	// Calculate position of player center
	Vec2 centroidPt;
	int xSum = 0, ySum = 0;

	for (int k = 0; k < nVerts; k++) {
		xSum += verts[k].x;
		ySum += verts[k].y;
	}

	centroidPt.x = (float)xSum / nVerts;
	centroidPt.y = (float)ySum / nVerts;

	// Set Geometric tranformation parameters
	Vec2 pivotPt = centroidPt;
	Vec2 fixedPt = centroidPt;
	Vec2 normal = GetSectionNormal(bullet->GetLeft(), bullet->GetRight());
	float desiredAngle = atan2(-normal.y, normal.x);
	float angle = desiredAngle - bullet->GetAngle();

	Vec2 bulletPos = bullet->GetPosition();
	bulletPos.x += normal.x * bullet->GetSpeed();
	bulletPos.y += normal.y * bullet->GetSpeed();

	Vec2 t = { bulletPos.x - centroidPt.x, bulletPos.y - centroidPt.y };								// Translation


	// Declare and initialize composite matrix to identity
	Matrix3x3 matComposite;
	GameMath::Matrix3x3SetIdentity(matComposite);

	// Construct composite matrix for transformation sequence
	GameMath::Scale2D(bullet->GetScale(), bullet->GetScale(), fixedPt, matComposite);
	GameMath::Rotate2D(pivotPt, angle, matComposite);
	GameMath::Translate2D(t.x, t.y, matComposite);


	// Apply composite matrix to bullet vertices
	GameMath::TransformVerts2D(nVerts, verts, matComposite);

	bullet->SetPosition(bulletPos);
	bullet->SetDestination(GetSectionBack(bullet->GetLeft(), bullet->GetRight()));
	bullet->SetDirection(GetSectionNormal(bullet->GetLeft(), bullet->GetRight()));

}

void Level::TransformEnemy(Enemy * enemy)
{
	// Bullet Geometry information
	int nVerts = enemy->VERTS();
	Vec2* verts = enemy->GetGeometry();

	// Calculate position of player center
	Vec2 centroidPt;
	int xSum = 0, ySum = 0;

	for (int k = 0; k < nVerts; k++) {
		xSum += verts[k].x;
		ySum += verts[k].y;
	}

	centroidPt.x = (float)xSum / nVerts;
	centroidPt.y = (float)ySum / nVerts;

	// Set Geometric tranformation parameter
	Vec2 enemyPos = enemy->GetPosition();

	Vec2 t = { enemyPos.x - centroidPt.x, enemyPos.y - centroidPt.y };								// Translation

	// Declare and initialize composite matrix to identity
	Matrix3x3 matComposite;
	GameMath::Matrix3x3SetIdentity(matComposite);

	// Construct composite matrix for transformation sequence
	GameMath::Translate2D(t.x, t.y, matComposite);

	// Apply composite matrix to bullet vertices
	GameMath::TransformVerts2D(nVerts, verts, matComposite);

	enemy->SetPosition(enemyPos);
}

void Level::PopulateSectionLengths()
{

	for (int i = 0; i < NUM_SECTIONS; i++) {

		int left = i, right = i + 1;

		if (i == NUM_SECTIONS - 1) right = 0;

		float sectionLength = GameMath::Distance(GetSectionTop(left, right), GetSectionBack(left, right));
		if (m_biggestSectionLength < sectionLength) m_biggestSectionLength = sectionLength;
		m_sectionLengths[i] = sectionLength;
	}
}

void Level::SuperZapper()
{
	for (auto &j : m_enemies) {
		j->SetAlive(false);
	}
}

Level::Level(Player * player, GameManager* gameManager)
{
	ptr_player = player;
	ptr_gameManager = gameManager;
	m_enemySpawner = new EnemySpawner(this);
}

void Level::Update(float deltaTime)
{
	if (ptr_player->IsAlive()) {
		TransformPlayer(deltaTime);

		for (auto &i : m_bullets) {
			i->Update(deltaTime);


			//Collsion detection: only check entities that are in the same lane currently
			if (i->IsEnemy()) {

				if (i->GetLeft() == m_currentSection[0]) {
					if (GameMath::Distance(i->GetPosition(), ptr_player->GetPosition()) < abs(ptr_player->HitRadius() - i->HitRadius())) {

						ptr_player->GetShot();
						i->setAlive(false);
						//RespawnPlayer();
					}
				}
			}
			else {
				for (auto &j : m_enemies) {

					if (j->GetLeft() == i->GetLeft()) {
						if (GameMath::Distance(j->GetPosition(), i->GetPosition()) < abs(i->HitRadius() - j->HitRadius())) {

							// Enemy  is hit by bullet, nice
							j->GetShot();
							i->setAlive(false);
							ptr_gameManager->AddToScore(1);
						}
					}
				}
			}
		}

		// EnemySpawner 
		m_enemySpawner->Update(deltaTime);

		for (auto &j : m_enemies) {
			j->Update(deltaTime);

			if (j->HurtOnTouch()) {

				if (j->GetLeft() == m_currentSection[0]) {
					if (GameMath::Distance(j->GetPosition(), ptr_player->GetPosition()) < abs(ptr_player->HitRadius() - j->HitRadius())) {

						ptr_player->GetShot();
						j->SetAlive(false);
						//RespawnPlayer();
					}
				}
			}
		}


		// Entity Cleanup -> object pooling eventually?
		auto i = m_bullets.begin();
		while (i != m_bullets.end()) {

			if (!(*i)->IsAlive()) {

				delete (*i);
				i = m_bullets.erase(i);

			}

			else ++i;

		}

		auto j = m_enemies.begin();
		while (j != m_enemies.end()) {

			if (!(*j)->IsAlive()) {

				ptr_gameManager->AddToScore(100);
				m_activeEnemies--;

				delete (*j);
				j = m_enemies.erase(j);

			}

			else ++j;

		}
	}
}

void Level::Draw()
{

	// Draw foreground
	Vec2 startPosFor = GetForground(0);
	Vec2 startPosBack = GetBackground(0);

	for (int i = 1; i < LEVEL_VERTS; i++) {

		Vec2 endPosFor = GetForground(i);
		Vec2 endPosBack = GetBackground(i);

		// Draw lines: 
		App::DrawLine(startPosFor.x, startPosFor.y, endPosFor.x, endPosFor.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);			// forground
		App::DrawLine(startPosBack.x, startPosBack.y, endPosBack.x, endPosBack.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);		// background

		if (i - 1 == m_currentSection[0] || i - 1 == m_currentSection[1])
			App::DrawLine(startPosFor.x, startPosFor.y, startPosBack.x, startPosBack.y, m_playerColor.r, m_playerColor.g, m_playerColor.b);
		else App::DrawLine(startPosFor.x, startPosFor.y, startPosBack.x, startPosBack.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);		// connect back to for

		startPosFor = endPosFor;
		startPosBack = endPosBack;

		// Final position
		if (i == LEVEL_VERTS - 1) {

			if (m_currentSection[0] == LEVEL_VERTS - 1 || i == m_currentSection[1])
				App::DrawLine(startPosFor.x, startPosFor.y, startPosBack.x, startPosBack.y, m_playerColor.r, m_playerColor.g, m_playerColor.b);
			else App::DrawLine(startPosFor.x, startPosFor.y, startPosBack.x, startPosBack.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);		// connect back to for

			// Connect looped levels
			if (m_loops) {

				endPosFor = GetForground(0);
				endPosBack = GetBackground(0);

				App::DrawLine(startPosFor.x, startPosFor.y, endPosFor.x, endPosFor.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);
				App::DrawLine(startPosBack.x, startPosBack.y, endPosBack.x, endPosBack.y, m_levelColor.r, m_levelColor.g, m_levelColor.b);
			}
		}
	}

	// Draw Bullets
	for (auto &i : m_bullets) {
		i->Draw();
	}

	// Draw Enemies
	for (auto &j : m_enemies) {
		j->Draw();
	}

	// Debugging...
	//Draw current section center
	//App::DrawLine(playerPos.x, playerPos.y, centerPos.x, centerPos.y, GameMath::Green.r, GameMath::Green.g, GameMath::Green.b);

}

void Level::SpawnBullet(bool enemyBullet, Vec2 position)
{

	float dampening = m_sectionLengths[GetSectionLeft()] / m_biggestSectionLength;

	Bullet* bullet = new Bullet(enemyBullet, position, GetSectionLeft(), GetSectionRight(), dampening);
	m_bullets.emplace_back(bullet);
	TransformBullet(bullet);

}

void Level::SpawnEnemy(EnemyType enemy, Vec2 position, int left)
{

	int right;
	if (left == 15) right = 0;
	else right = left + 1;

	switch (enemy) {
	case EnemyType::SPIKE:

		Enemy* enemy = new Spike(position, GetSectionTop(left, right), GetSectionBack(left, right), {(float)left, (float)right}, m_speedAdjustment);

		m_enemies.emplace_back(enemy);
		TransformEnemy(enemy);
		break;
	}

	m_activeEnemies++;
}

void Level::MoveLeft()
{
	m_hasMoved = true;

	if (m_currentSection[0] > 0 && m_currentSection[1] > 0) {

		m_currentSection[0]--;
		m_currentSection[1]--;


	}
	else if (m_currentSection[0] == LEVEL_VERTS - 1) {

		m_currentSection[0]--;
		m_currentSection[1] = LEVEL_VERTS - 1;

	}
	else {

		if (m_loops) {

			m_currentSection[0] = LEVEL_VERTS - 1;
			m_currentSection[1] = 0;

		}
		else m_hasMoved = false;
	}

}

void Level::MoveRight()
{
	m_hasMoved = true;

	if (m_currentSection[0] < LEVEL_VERTS - 1 && m_currentSection[1] < LEVEL_VERTS - 1) {

		m_currentSection[0]++;
		m_currentSection[1]++;


	}
	else if (m_currentSection[0] == LEVEL_VERTS - 1) {

		m_currentSection[0] = 0;
		m_currentSection[1] ++;

	}
	else {

		if (m_loops) {

			m_currentSection[0] = LEVEL_VERTS - 1;
			m_currentSection[1] = 0;


		}
		else	m_hasMoved = false;
	}
}


Level::~Level()
{

	delete m_enemySpawner;

	for (auto &i : m_bullets) {
		delete i;
	}

	for (auto &j : m_enemies) {
		delete j;
	}

	
	ptr_player->DoneLoading(false);
}
