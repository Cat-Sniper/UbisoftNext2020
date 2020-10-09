#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_VERTS 8

class Player {

private:

	// Position of player on screen: centre of two level vertices
	Vec2 m_position;	

	// Player Geometry with pivot at center 
	Vec2 m_geometry[PLAYER_VERTS] = {	{ 0,-2}, {-3, 0}, {-1, 1}, {-2, 0},
									{ 0,-1}, { 2, 0}, { 1, 1}, { 3, 0}  };

	// # of super zappers available to use on this level
	int m_remainingSupers;
	bool m_isAlive;
	bool m_levelLoaded = false;
	int m_section;
	float m_hitRadius;
	float m_angle = 0.0f;
	float m_scale = 1.0f;

	Color m_color = GameMath::Yellow;

	int m_remainingLives;

	float m_timeSinceDeath;
	float m_currentTime;
	float m_respawnTime = 1000.0f;

	
public:
	static const int VERTS = PLAYER_VERTS;

	Player();
	void Init();
	void Draw();
	void Update(float deltaTime);

	int GetSuper() { return m_remainingSupers; }
	void UseSuper() { m_remainingSupers--; }
	Vec2 GetPosition() { return m_position; }
	void SetPosition(Vec2 position) { m_position = position; }
	Vec2 GetGeometry(int i) { return m_geometry[i]; }
	Vec2* GetGeometry() { return m_geometry; }
	bool IsAlive() { return m_isAlive; }
	bool HasLivesLeft() { return (m_remainingLives > 0); }

	

	void SetAngle(float angle) { m_angle = angle; }
	float GetAngle() { return m_angle; }
	float HitRadius() { return m_hitRadius; }
	void SetScale(float scale) { m_scale = scale; }
	float GetScale() { return m_scale; }
	void GetShot();
	void DoneLoading(bool load) { m_levelLoaded = load; if (load) m_remainingSupers = 1; }
	int GetLives() { return m_remainingLives; }
	void SetColor(Color col) { m_color = col; }
};
#endif