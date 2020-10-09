#include "stdafx.h"
#include "GameMath.h"

// Construct 3x3 Identity Matrix
void GameMath::Matrix3x3SetIdentity(Matrix3x3 matIdent3x3)
{
	int row, col;
	
	for (row = 0; row < 3; row++) {
		
		for (col = 0; col < 3; col++) {

			if(row == col) matIdent3x3[row][col] = 1;
			else			matIdent3x3[row][col] = 0;

		}
	}
			
		
}

// Premultiply matrix m1 times matrix m2, store result in m2
void GameMath::Matrix3x3PreMultiply(Matrix3x3 m1, Matrix3x3 m2) 
{
	int row, col;
	Matrix3x3 matTemp;

	for (row = 0; row < 3; row++)
		for (col = 0; col < 3; col++)
			matTemp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col];

	for (row = 0; row < 3; row++)
		for (col = 0; col < 3; col++)
			m2[row][col] = matTemp[row][col];
}

// Add the translation component to the input composite matrix
void GameMath::Translate2D(float tx, float ty, Matrix3x3 matComposite)
{
	Matrix3x3 matTransl;

	// Initialize translation matrix to identity
	Matrix3x3SetIdentity(matTransl);

	matTransl[0][2] = tx;
	matTransl[1][2] = ty;

	// Concatenate matTransl with the composite matrix.
	Matrix3x3PreMultiply(matTransl, matComposite);
}

// Add the rotation component to the input composite matrix
void GameMath::Rotate2D(Vec2 pivot, float angle, Matrix3x3 matComposite)
{
	Matrix3x3 matRot;

	// Initialize rotation matrix
	Matrix3x3SetIdentity(matRot);

	matRot[0][0] = cos(angle);
	matRot[0][1] = -sin(angle);
	matRot[0][2] = pivot.x * (1 - cos(angle)) + pivot.y * sin(angle);

	matRot[1][0] = sin(angle);
	matRot[1][1] = cos(angle);
	matRot[1][2] = pivot.y * (1 - cos(angle)) - pivot.x * sin(angle);

	// Concatenate matRot with the composite matrix
	Matrix3x3PreMultiply(matRot, matComposite);
}

void GameMath::Scale2D(float sx, float sy, Vec2 fixedPt, Matrix3x3 matComposite)
{
	Matrix3x3 matScale;

	Matrix3x3SetIdentity(matScale);

	matScale[0][0] = sx;
	matScale[0][2] = (1 - sx) * fixedPt.x;
	matScale[1][1] = sy;
	matScale[1][2] = (1 - sy) * fixedPt.y;

	Matrix3x3PreMultiply(matScale, matComposite);
}

// Using a composite matrix, calculate transformed coordinates.
void GameMath::TransformVerts2D(int nVerts, Vec2 *verts, Matrix3x3 matComposite)
{


	for (int k = 0; k < nVerts; k++) {
		float temp = matComposite[0][0] * verts[k].x + matComposite[0][1] * verts[k].y + matComposite[0][2];
		verts[k].y = matComposite[1][0] * verts[k].x + matComposite[1][1] * verts[k].y + matComposite[1][2];
		verts[k].x = temp;
	}
}

float GameMath::Distance(Vec2 start, Vec2 end)
{
	float x2 = (end.x - start.x) * (end.x - start.x);
	float y2 = (end.y - start.y) * (end.y - start.y);
	return sqrtf(x2 + y2);
}

Vec2 GameMath::NormalizeDirection(Vec2 start, Vec2 end)
{
	Vec2 direction = { end.x - start.x , end.y - start.y };
	float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
	return { direction.x /= length, direction.y /= length };
}


