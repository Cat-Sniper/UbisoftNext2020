#ifndef TYPES_H
#define TYPES_H

struct Vec2 {
	float x = 0;
	float y = 0;
};

struct Color {
	float r, g, b;
};

typedef float Matrix3x3[3][3];

enum EnemyType {
	SPIKE
};

enum GameState {
	MENU,
	PAUSED,
	WARPING,
	GAMEPLAY,
	GAMEOVER,
	LOAD
};
#endif