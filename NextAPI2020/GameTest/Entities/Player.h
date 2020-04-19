#ifndef PLAYER_H
#define PLAYER_H

#define GEOMETRY_VERTS 8

class Player {

private:

	// Position of player on screen: centre of two level vertices
	Vec2 m_position;	

	// Player Geometry with pivot at center 
	Vec2 m_geometry[GEOMETRY_VERTS] = {	{ 0,-2}, {-3, 0}, {-1, 1}, {-2, 0},	
									{ 0,-1}, { 2, 0}, { 1, 1}, { 3, 0}  };

	// # of super zappers available to use on this level
	int m_remainingSupers;

	float m_angle = 0.0f;
	Vec2 m_scale = { 1.0f, 1.0f };

	
public:
	static const int VERTS = GEOMETRY_VERTS;

	Player();

	void Draw();
	int GetSuper() { return m_remainingSupers; }
	Vec2 GetPosition() { return m_position; }
	void SetPosition(Vec2 position) { m_position = position; }
	Vec2 GetGeometry(int i) { return m_geometry[i]; }
	Vec2* GetGeometry() { return m_geometry; }

	

	void SetAngle(float angle) { m_angle = angle; }
	float GetAngle() { return m_angle; }

	void SetScale(Vec2 scale) { m_scale = scale; }
	Vec2 GetScale() { return m_scale; }
};
#endif