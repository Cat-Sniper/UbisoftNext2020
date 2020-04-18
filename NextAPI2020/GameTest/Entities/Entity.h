#ifndef ENTITY_H
#define ENTITY_H

#include "..\stdafx.h"
#include "..\app\app.h"
class Entity {

protected:

	// Position
	Vec2 m_position;

	// Entity sprite
	CSimpleSprite *m_sprite;

	bool m_isAlive = true;

public:
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	void SetPosition(Vec2 position)  { m_position = position; }
	void GetPosition(Vec2 &position) { position = m_position; }
	bool IsAlive() { return m_isAlive; }
	CSimpleSprite* GetSprite() { return m_sprite; }

	virtual ~Entity() {
		delete m_sprite;
	};

};
#endif