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

Vector4 Matrix::operator*(const Vector4& other) const
{
	Vector4 vec = Vector4();

	vec.x = m[0][0] * other.x + m[0][1] * other.y + m[0][2] * other.z + m[0][3] * other.w;
	vec.y = m[1][0] * other.x + m[1][1] * other.y + m[1][2] * other.z + m[1][3] * other.w;
	vec.z = m[2][0] * other.x + m[2][1] * other.y + m[2][2] * other.z + m[2][3] * other.w;
	vec.w = m[3][0] * other.x + m[3][1] * other.y + m[3][2] * other.z + m[3][3] * other.w;

	return vec;
}


Matrix Matrix::GetMRoteX(float angleX)
{
	Matrix matrix = Matrix();

	float Cos = cosf(MyMath::EulerToRad(angleX));
	float Sin = sinf(MyMath::EulerToRad(angleX));

	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = Cos;
	matrix.m[1][2] = -Sin;
	matrix.m[2][0] = Sin;
	matrix.m[2][1] = Cos;
	matrix.m[3][3] = 1.0f;

	return matrix;
}

Matrix Matrix::GetUnit()
{
	Matrix matrix = Matrix();

	for (int i = 0; i < 4; i++) {
		matrix.m[i][i] = 1.0f;
	}

	return matrix;
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

Matrix Matrix::GetMRoteZ(float angleZ)
{
	Matrix matrix = Matrix();

	float Cos = cosf(MyMath::EulerToRad(angleZ));
	float Sin = sinf(MyMath::EulerToRad(angleZ));

	matrix.m[0][0] = Cos;
	matrix.m[0][2] = Sin;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][0] = -Sin;
	matrix.m[2][1] = Cos;
	matrix.m[3][3] = 1.0f;

	return matrix;
}

Matrix Matrix::GetMRote(Vector3 angleVec)
{
	return GetMRoteZ(angleVec.z) * GetMRoteX(angleVec.x) * GetMRoteY(angleVec.y);
}

Matrix Matrix::GetMScale(Vector3 scaleVec)
{
	Matrix matrix = Matrix();

	matrix.m[0][0] = scaleVec.x;
	matrix.m[1][1] = scaleVec.y;
	matrix.m[2][2] = scaleVec.z;
	matrix.m[3][3] = 1.0f;

	return matrix;
}

Matrix Matrix::GetMMatrix(Vector3 transVec, Vector3 roteVec, Vector3 scaleVec)
{
	return Matrix::GetMTrans(transVec) * Matrix::GetMRote(roteVec) * Matrix::GetMScale(scaleVec);
}

Matrix Matrix::GetMTrans(Vector3 transVec)
{
	Matrix matrix = Matrix::GetUnit();

	matrix.m[0][3] = transVec.x;
	matrix.m[1][3] = transVec.y;
	matrix.m[2][3] = transVec.z;

	return matrix;
}

