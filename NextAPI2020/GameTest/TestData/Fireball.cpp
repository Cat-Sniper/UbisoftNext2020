#include "stdafx.h"
#include "Fireball.h"


/* Fireball Constructor. Needs to know how long to live, position, and angle
*
*/
Fireball::Fireball(float timeAlive, float x, float y, float angle) {
	m_sprite = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	m_sprite->SetFrame(11);
	m_sprite->SetScale(1.0F);
	m_sprite->SetPosition(x, y);
	m_sprite->SetAngle( angle - PI/2 );
	m_timeRemaining = timeAlive;
	m_angle = angle;

	m_rigidbody = new RigidBody(x, y, angle, 10, m_sprite->GetWidth(), m_sprite->GetHeight());
	m_rigidbody->ApplyForce(m_speed * cosf(m_angle), m_speed * sinf(m_angle), ForceMode::IMPULSE);
}
Fireball::~Fireball() {
	delete m_rigidbody;
}

void Fireball::Update(float dt) {
	if (m_isAlive) {
		m_sprite->Update(dt);

		m_rigidbody->SimulateRigidbody(dt);
		

		// Update position of sprite based on rigidbody
		float x, y;
		m_rigidbody->GetPosition(x, y);
		m_sprite->SetPosition(x, y);
		m_sprite->SetAngle(m_rigidbody->GetAngle());
		m_timeRemaining -= dt;

		if (m_timeRemaining <= 0) {
			m_isAlive = false;
		}
	}
}

void Fireball::Draw() {
	if(m_isAlive) m_sprite->Draw();
}