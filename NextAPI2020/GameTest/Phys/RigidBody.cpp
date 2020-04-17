#include "stdafx.h"
#include "RigidBody.h"

#include <iostream>
void RigidBody::ComputeForceAndTorque() {
	Vector2 arm = {m_shape.width / 2, m_shape.height / 2 };
	m_torque = arm.x * m_force.y - arm.y * m_force.x;

	if (m_forceMode == ForceMode::IMPULSE) {
		m_force.x *= 0.9;
		m_force.y *= 0.9;
	}
}

RigidBody::RigidBody() {
}

RigidBody::RigidBody(float x, float y, float angle, float mass, float width, float height) {
	m_position.x = x;
	m_position.y = y;
	m_angle = angle;
	InitializeShape(mass, width, height);
}

RigidBody::~RigidBody() {
}

void RigidBody::PrintRigidBody() {
}

void RigidBody::InitializeShape(float mass, float width, float height) {
	m_shape.mass = mass;
	m_shape.width = width;
	m_shape.height = height;
	m_shape.CalculateBoxInertia();
}

void RigidBody::SimulateRigidbody(float dt) {
	float deltaTime = dt / 100;
	ComputeForceAndTorque();
	Vector2 linearAcceleration = { m_force.x / m_shape.mass, m_force.y / m_shape.mass };

	switch (m_forceMode) {
	case CONSTANT:
		m_linearVelocity.x += linearAcceleration.x * deltaTime;
		m_linearVelocity.y += linearAcceleration.y * deltaTime;
		break;
	case IMPULSE:
		
		m_linearVelocity.x += linearAcceleration.x * deltaTime;
		m_linearVelocity.y += linearAcceleration.y * deltaTime;
	}
	
	m_position.x += m_linearVelocity.x * deltaTime;
	m_position.y += m_linearVelocity.y * deltaTime;
	float angularAcceleration = m_torque / m_shape.momentOfInertia;
	m_angularVelocity += angularAcceleration * deltaTime;
	m_angle += m_angularVelocity * deltaTime;
}
