#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "..\app\app.h"

class Entity {

protected:

	// Position
	float m_xPos = 0.0F;
	float m_yPos = 0.0F;

	// Entity sprite
	CSimpleSprite *m_sprite;
	
	bool m_isAlive = true;

public:
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	void SetPosition(float x, float y) { m_xPos = x; m_yPos = y; }
	void GetPosition(float &x, float &y) { x = m_xPos; y = m_yPos; }
	bool IsAlive() { return m_isAlive; }
	CSimpleSprite* GetSprite() { return m_sprite; }

	virtual ~Entity() {
		delete m_sprite;
	};

};
#endif