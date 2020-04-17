#include "stdafx.h"
#include "TestSquare.h"

TestSquare::TestSquare(float x, float y, float angle) {
	m_sprite = App::CreateSprite(".\\TestData\\square.bmp", 1, 1);
	m_sprite->SetFrame(0);
	m_sprite->SetScale(1.0F);
	m_sprite->SetPosition(x, y);
	m_sprite->SetAngle(angle);
	
	m_rigidbody = new RigidBody(x, y, angle, 10, m_sprite->GetWidth(), m_sprite->GetHeight());
	m_rigidbody->ApplyForce(0, 100, ForceMode::CONSTANT);

}

TestSquare::~TestSquare() {
	delete m_rigidbody;
}

void TestSquare::Draw() {
	m_sprite->Draw();
}

void TestSquare::Update(float dt) {
	m_sprite->Update(dt);

	m_rigidbody->SimulateRigidbody(dt);

	float x, y;
	m_rigidbody->GetPosition(x, y);
	m_sprite->SetPosition(x, y);
	m_sprite->SetAngle(m_rigidbody->GetAngle());

}

