#ifndef BULLET_H
#define BULLET_H



class Bullet {
#define BULLET_VERTS 16
#define INITIAL_RADIUS 15.0f

private:
	Vec2 m_startPosition;
	Vec2 m_destination;
	Vec2 m_position = { 0,0 };
	float m_distance;

	bool m_isAlive = true;
	bool m_enemyBullet;
	int m_section[2];		
	Vec2 m_direction;


	float m_speed = 7.0f;
	float m_speedDampener = 0;
	float m_scale = 1.0f;
	float m_lastScale;
	float m_angle = 0.0f;

	Vec2 m_geometry[BULLET_VERTS] = { 
		{3,0}, {2,-1},{2,-2},{1,-2},
		{0,-3},{-1,-2},{-2,-2},{-2,-1},
		{-3,0},{-2,1},{-2,2},{-1,2},
		{0,3},{1,2},{2,2},{2,1}
	};
public:
	static const int VERTS = BULLET_VERTS;

	Bullet(bool enemyBullet, Vec2 position, int sectionLeft, int sectionRight, float speedDamp);

	void Draw();
	void Update(float deltaTime);
	void SetPosition(Vec2 position) { m_position = position; m_startPosition = position; }
	Vec2 GetPosition() { return m_position; }
	void SetDirection(Vec2 normal) { m_direction = normal; }
	void SetDestination(Vec2 dest);
	float GetAngle() { return m_angle; }

	bool IsEnemy() { return m_enemyBullet; }
	Vec2* GetGeometry() { return m_geometry; }
	int GetLeft() { return m_section[0]; }
	int GetRight() { return m_section[1]; }
	float GetSpeed() { return m_speed; }
	float GetScale() { return m_scale; }
	float HitRadius() { return INITIAL_RADIUS * m_scale; }
	void setAlive(bool alive) { m_isAlive = alive; }
	bool IsAlive() { return m_isAlive; }

};
#endif