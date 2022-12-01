#include "Matrix.h"

Matrix Matrix::operator*(const Matrix& other) const
{
	Matrix matrix = Matrix();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				matrix.m[i][j] += m[i][k] * other.m[k][j];
			}
		}
	}

	return matrix;
}

Vector3 Matrix::operator*(const Vector3& other) const
{
	Vector3 vec;

	vec.x = m[0][0] * other.x + m[0][1] * other.y + m[0][2] * other.z + m[0][3] * 1.0f;
	vec.y = m[1][0] * other.x + m[1][1] * other.y + m[1][2] * other.z + m[1][3] * 1.0f;
	vec.z = m[2][0] * other.x + m[2][1] * other.y + m[2][2] * other.z + m[2][3] * 1.0f;

	return vec;
}

Matrix Matrix::GetUnit()
{
	Matrix matrix = Matrix();

	for (int i = 0; i < 4; i++) {
		matrix.m[i][i] = 1.0f;
	}

	return matrix;
}

Matrix Matrix::GetMRoteX(float angleX)
{
	Matrix matrix = Matrix();

	float Cos = cosf(MyMath::EulerToRad(angleX));
	float Sin = sinf(MyMath::EulerToRad(angleX));

	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = Cos;
	matrix.m[1][2] = -Sin;
	matrix.m[2][1] = Sin;
	matrix.m[2][2] = Cos;
	matrix.m[3][3] = 1.0f;

	return matrix;
}

Matrix Matrix::GetMRoteX(const Vector3& centerPoint, float angleX)
{
	Matrix mTrans = Matrix::GetMTrans(-centerPoint);	//���_�Ɉړ�
	Matrix mTransBack = Matrix::GetMTrans(centerPoint);	//���ɖ߂�
	Matrix mRotateX = Matrix::GetMRoteX(angleX);	//���_���S�ɉ�]

	return mTransBack * mRotateX * mTrans;
}

Matrix Matrix::GetMRoteY(float angleY)
{
	Matrix matrix = Matrix();

	float Cos = cosf(MyMath::EulerToRad(angleY));
	float Sin = sinf(MyMath::EulerToRad(angleY));

	matrix.m[0][0] = Cos;
	matrix.m[0][2] = Sin;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][0] = -Sin;
	matrix.m[2][2] = Cos;
	matrix.m[3][3] = 1.0f;

	return matrix;
}

Matrix Matrix::GetMRoteY(const Vector3& centerPoint, float angleY)
{
	Matrix mTrans = Matrix::GetMTrans(-centerPoint);	//���_�Ɉړ�
	Matrix mTransBack = Matrix::GetMTrans(centerPoint);	//���ɖ߂�
	Matrix mRotateY = Matrix::GetMRoteY(angleY);	//���_���S�ɉ�]

	return mTransBack * mRotateY * mTrans;
}

Matrix Matrix::GetMRoteZ(float angleZ)
{
	Matrix matrix = Matrix();

	float Cos = cosf(MyMath::EulerToRad(angleZ));
	float Sin = sinf(MyMath::EulerToRad(angleZ));

	matrix.m[0][0] = Cos;
	matrix.m[0][1] = -Sin;
	matrix.m[1][0] = Sin;
	matrix.m[1][1] = Cos;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;

	return matrix;
}

Matrix Matrix::GetMRoteZ(const Vector3& centerPoint, float angleZ)
{
	Matrix mTrans = Matrix::GetMTrans(-centerPoint);	//���_�Ɉړ�
	Matrix mTransBack = Matrix::GetMTrans(centerPoint);	//���ɖ߂�
	Matrix mRotateZ = Matrix::GetMRoteZ(angleZ);	//���_���S�ɉ�]

	return mTransBack * mRotateZ * mTrans;
}

Matrix Matrix::GetMRote(const Vector3& angleVec)
{
	return GetMRoteY(angleVec.y) * GetMRoteX(angleVec.x) * GetMRoteZ(angleVec.z);
}

Matrix Matrix::GetMRote(const Vector3& centerPoint, const Vector3& angleVec)
{
	Matrix mTrans = Matrix::GetMTrans(-centerPoint);	//���_�Ɉړ�
	Matrix mTransBack = Matrix::GetMTrans(centerPoint);	//���ɖ߂�
	Matrix mRotate = Matrix::GetMRote(angleVec);	//���_���S�ɉ�]

	return mTransBack * mRotate * mTrans;
}

Matrix Matrix::GetMScale(const Vector3& scaleVec)
{
	Matrix matrix = Matrix();

	matrix.m[0][0] = scaleVec.x;
	matrix.m[1][1] = scaleVec.y;
	matrix.m[2][2] = scaleVec.z;
	matrix.m[3][3] = 1.0f;

	return matrix;
}

Matrix Matrix::GetMScale(const Vector3& centerPoint, const Vector3& scaleVec)
{
	Matrix mTrans = Matrix::GetMTrans(-centerPoint);	//���_�Ɉړ�
	Matrix mTransBack = Matrix::GetMTrans(centerPoint);	//���ɖ߂�
	Matrix mScale = Matrix::GetMScale(scaleVec);	//���_���S�Ɋg��

	return mTransBack * mScale * mTrans;
}

Matrix Matrix::GetMMatrix(const Vector3& transVec, const Vector3& roteVec, const Vector3& scaleVec)
{
	return Matrix::GetMTrans(transVec) * Matrix::GetMRote(roteVec) * Matrix::GetMScale(scaleVec);
}

Matrix Matrix::GetMTrans(const Vector3& transVec)
{
	Matrix matrix = Matrix::GetUnit();

	matrix.m[0][3] = transVec.x;
	matrix.m[1][3] = transVec.y;
	matrix.m[2][3] = transVec.z;

	return matrix;
}

