#include "SetMatrix.h"

Matrix4 CreatematWorld(WorldTransform w)
{
	Matrix4 matIdentity;
	matIdentity.m[0][0] = 1;
	matIdentity.m[1][1] = 1;
	matIdentity.m[2][2] = 1;
	matIdentity.m[3][3] = 1;

	Matrix4 matScale;

	matScale.m[0][0] = w.scale_.x;
	matScale.m[1][1] = w.scale_.y;
	matScale.m[2][2] = w.scale_.z;
	matScale.m[3][3] = 1;
	
	Matrix4 matTrans = MathUtility::Matrix4Identity();
	matTrans.m[3][0] = w.translation_.x;
	matTrans.m[3][1] = w.translation_.y;
	matTrans.m[3][2] = w.translation_.z;
	matTrans.m[3][3] = 1;

	Matrix4 matWorld = MathUtility::Matrix4Identity();

	matWorld *= matScale;
	matWorld *= matTrans;


	return	matWorld;

}
