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

#endif