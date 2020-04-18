#ifndef LEVEL_H
#define LEVEL_H

class Player;

class Level {
protected:
	Vec2 m_foregroundGeometry[16];
	Vec2 m_backgroundGeometry[16];

	const int m_nVerts = 16;
	bool m_loops;
	bool m_hasMoved;
	int m_currentSection[2];				// index of the two vertices the player is touching. This defines the section the player is in
	Player* ptr_player;
public:

	virtual void Update(float deltaTime) = 0;
	virtual Vec2 GetForground(int i) = 0;
	virtual Vec2 GetBackground(int i) = 0;
	virtual Vec2 GetSectionCenter() = 0;
	virtual Vec2 GetSectionNormal() = 0;
	virtual Vec2 GetPlayerCenter() = 0;


	virtual void TransformPlayer() = 0;
	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;

	int GetVerts() { return m_nVerts; }
	bool DoesLoop() { return m_loops; }
};
#endif