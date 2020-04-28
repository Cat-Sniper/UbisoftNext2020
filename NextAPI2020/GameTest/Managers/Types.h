#ifndef TYPES_H
#define TYPES_H

#define NUM_STOPS 15
#define LEVEL_VERTS 16
#define NUM_SECTIONS 16
#define MAX_VERTS 16

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