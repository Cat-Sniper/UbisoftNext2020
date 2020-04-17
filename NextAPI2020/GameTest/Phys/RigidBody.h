#pragma once
#ifndef RIGIDBODY_H
#define RIGIDBODY_H
struct Vector2 {
	float x = 0;
	float y = 0;
};
struct BoxShape {
	float width = 0;
	float height = 0;
	float mass = 0;
	float momentOfInertia = 0;

	void CalculateBoxInertia() {
		momentOfInertia = mass * (width * width + height * height) / 12;
	}
};

enum ForceMode {
	CONSTANT,
	IMPULSE
};

class RigidBody {

private:
	Vector2 m_position;
	Vector2 m_linearVelocity;
	Vector2 m_force;
	float m_angle;
	float m_angularVelocity;
	float m_torque;
	BoxShape m_shape;
	ForceMode m_forceMode;

	void ComputeForceAndTorque();
	

public:
	RigidBody();
	RigidBody(float x, float y, float angle, float mass, float width, float height);
	~RigidBody();

	void PrintRigidBody();
	void InitializeShape(float mass, float width, float height);
	void SimulateRigidbody(float dt);

	void SetPosition(float x, float y) { m_position.x = x; m_position.y = y; }
	void GetPosition(float &x, float &y) { x = m_position.x; y = m_position.y; }
	void SetLinearVelocity(float x, float y) { m_linearVelocity.x = x; m_linearVelocity.y = y; }
	void ApplyForce(float x, float y, ForceMode force) { m_force.x = x; m_force.y = y; m_forceMode = force; }
	void SetAngle(float rad) { m_angle = rad; }
	float GetAngle() { return m_angle; }
	BoxShape GetShape() { return m_shape; }

};
#endif