#include "stdafx.h"
#include "CircleLevel.h"

#include "Entities/Player.h"
#include "Entities/Bullet.h"
#include "Entities/Enemies/Spike.h"
#include "Managers/GameMath.h"
#include "App/app.h"

CircleLevel::CircleLevel(Player* player) 

{
	ptr_player = player;
	m_loops = true;
	m_hasMoved = true;
	
	m_currentSection[0] = 13;
	m_currentSection[1] = 14;

	m_levelColor = GameMath::Blue;
	m_playerColor = GameMath::Yellow;

	// Initialize Level Geometry
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

	// Scale geometry 
	for (int i = 0; i < m_nVerts; i++) {
		
		m_foregroundGeometry[i].x += 20.0f;
		m_foregroundGeometry[i].y += 16.0f;
		m_backgroundGeometry[i].x += 20.0f;
		m_backgroundGeometry[i].y += 14.0f;

		m_foregroundGeometry[i].x *= 25.0f;
		m_foregroundGeometry[i].y *= 25.0f;
		m_backgroundGeometry[i].x *= 25.0f;
		m_backgroundGeometry[i].y *= 25.0f;
		
	}

}

CircleLevel::~CircleLevel()
{

}

void CircleLevel::Update(float deltaTime) {

	TransformPlayer(deltaTime);

	for (auto &i : m_bullets) {
		i->Update(deltaTime);
	}

	for (auto &j : m_enemies) {
		j->Update(deltaTime);
	}


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

			delete (*j);
			j = m_enemies.erase(j);

		}

		else ++j;

	}
	
}
// Use midpoint formula on the background geometry of the current section
Vec2 CircleLevel::GetSectionBack(int left, int right)
{
	return { (m_backgroundGeometry[left].x + m_backgroundGeometry[right].x) / 2,
		    (m_backgroundGeometry[left].y + m_backgroundGeometry[right].y) / 2 };

}

Vec2 CircleLevel::GetSectionNormal(int left, int right)
{
	// Direction Vector
	Vec2 d = { m_foregroundGeometry[right].x - m_foregroundGeometry[left].x,
		    m_foregroundGeometry[right].y - m_foregroundGeometry[left].y };
	
	// Normalize
	float length = sqrtf(d.x * d.x + d.y * d.y);
	return { d.x /= length, d.y /= length };
}

Vec2 CircleLevel::GetBulletDirection(int left, int right)
{
	Vec2 back = GetSectionBack(left, right);
	Vec2 front = GetSectionTop(left, right);

	
	Vec2 direction = { back.x - front.x , back.y - front.y };
	float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
	return { direction.x /= length, direction.y /= length };
}

Vec2 CircleLevel::GetSectionTop(int left, int right) {
	return { (m_foregroundGeometry[left].x + m_foregroundGeometry[right].x) / 2,
		    (m_foregroundGeometry[left].y + m_foregroundGeometry[right].y) / 2 };
}

Vec2 CircleLevel::GetSectionTop()
{
	return GetSectionTop(GetSectionLeft(), GetSectionRight());
}

void CircleLevel::MoveRight() {

	m_hasMoved = true;

	if (m_currentSection[0] < m_nVerts -1 && m_currentSection[1] < m_nVerts - 1) {

		m_currentSection[0]++;
		m_currentSection[1]++;
		

	} else if (m_currentSection[0] == m_nVerts - 1) {

		m_currentSection[0] = 0;
		m_currentSection[1] ++;
		
	} else {

		if (m_loops) {

			m_currentSection[0] = m_nVerts - 1;
			m_currentSection[1] = 0;
			

		}
		else	m_hasMoved = false; 
	}
}

void CircleLevel::MoveLeft() {

	m_hasMoved = true;

	if (m_currentSection[0] > 0 && m_currentSection[1] > 0) {

		m_currentSection[0]--;
		m_currentSection[1]--;
		

	}
	else if (m_currentSection[0] == m_nVerts-1) {

		m_currentSection[0]--;
		m_currentSection[1] = m_nVerts - 1;

	} else {

		if (m_loops) {

			m_currentSection[0] = m_nVerts - 1;
			m_currentSection[1] = 0;

		} else m_hasMoved = false;
	}
}

void CircleLevel::TransformPlayer(float deltaTime) {


	// Player Geometry information
	int nVerts = Player::VERTS;
	Vec2* verts = ptr_player->GetGeometry();

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
	Vec2 normal = GetSectionNormal(m_currentSection[0], m_currentSection[1]);
	
	float desiredAngle = atan2(-normal.y, -normal.x); // Get angle defined as a surface normal by the line between the two points (-normal.x to compensate for 90 degree rotation of model)
	float angle = desiredAngle - ptr_player->GetAngle();

	// Declare and initialize composite matrix to identity
	Matrix3x3 matComposite;
	GameMath::Matrix3x3SetIdentity(matComposite);

	// Construct composite matrix for transformation sequence
	GameMath::Scale2D(ptr_player->GetScale().x, ptr_player->GetScale().y, fixedPt, matComposite);
	GameMath::Rotate2D(pivotPt, angle, matComposite);
	GameMath::Translate2D(t.x, t.y, matComposite);


	// Apply composite matrix to player vertices
	GameMath::TransformVerts2D(nVerts, verts, matComposite);

	//ptr_player->SetAngle(atan2(matComposite[1][2], -matComposite[2][2]));
	ptr_player->SetAngle(desiredAngle);
	ptr_player->SetPosition(centroidPt);
	m_hasMoved = false;
	

	
}

void CircleLevel::TransformBullet(Bullet * bullet)
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
	float desiredAngle = atan2(-normal.y, normal.x); // Get angle defined as a surface normal by the line between the two points (-normal.x to compensate for 90 degree rotation of model)
	float angle = desiredAngle - bullet->GetAngle();

	Vec2 bulletPos = bullet->GetPosition();
	bulletPos.x += normal.x * bullet->GetSpeed();
	bulletPos.y += normal.y * bullet->GetSpeed();

	Vec2 t = { bulletPos.x- centroidPt.x, bulletPos.y - centroidPt.y };								// Translation
	
	

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
	bullet->SetDirection(GetBulletDirection(bullet->GetLeft(), bullet->GetRight()));
	
	

}

void CircleLevel::TransformEnemy(Enemy * enemy)
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

void CircleLevel::SpawnBullet(bool enemyBullet, Vec2 position) {
	Bullet* bullet = new Bullet(enemyBullet, position, GetSectionLeft(), GetSectionRight());
	m_bullets.emplace_back(bullet);
	TransformBullet(bullet);
}

void CircleLevel::SpawnEnemy(EnemyType enemy, Vec2 position) {

	switch (enemy) {
	case EnemyType::SPIKE:
		Enemy* enemy = new Spike(position);
		m_enemies.emplace_back(enemy);
		TransformEnemy(enemy);
		break;
	}
}