#ifndef GAMEMATH_H
#define GAMEMATH_H

#include <math.h>
#include <ratio>

namespace GameMath {

	void Matrix3x3SetIdentity(Matrix3x3 matIdent3x3);
	void Matrix3x3PreMultiply(Matrix3x3 m1, Matrix3x3 m2);

	// Transformations
	void Translate2D(float tx, float ty, Matrix3x3 matComposite);
	void Rotate2D(Vec2 pivot, float angle, Matrix3x3 matComposite);
	void Scale2D(float sx, float sy, Vec2 fixedPt, Matrix3x3 matComposite);
	void TransformVerts2D(int nVerts, Vec2* verts, Matrix3x3 matComposite);


	float Distance(Vec2 start, Vec2 end);
	
	//Linear Interpolation
	Vec2 RandomPosition(Vec2 start, Vec2 end);

	Vec2 NormalizeDirection(Vec2 start, Vec2 end);

	static Color Blue{ 0.141f, 0.482f, 0.627f };
	static Color Green{ 0.164f, 0.498f, 0.384f };
	static Color Yellow{ 1.0f, 0.878f, 0.4f };
	static Color Orange{ 1.0f, 0.513f, 0.376f };
	static Color Red{ 0.949f, 0.372f, 0.360f };

}
#endif
