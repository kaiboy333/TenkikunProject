#pragma once
#include "Vector3.h"
#include <math.h>
#include "MyMath.h"
#include "Vector4.h"

class Matrix
{
	public:
		float m[4][4] = {};

		Matrix operator*(const Matrix& other) const;	//�s��̊|���Z
		Vector4 operator*(const Vector4& other) const;	//�s��ƃx�N�g���̊|���Z

		static Matrix GetUnit();	//�P�ʍs���Ԃ�

		static Matrix GetMRoteX(float angleX);
		static Matrix GetMRoteY(float angleY);
		static Matrix GetMRoteZ(float angleZ);
		static Matrix GetMRote(Vector3 angleVec);

		static Matrix GetMScale(Vector3 scaleVec);

		static Matrix GetMTrans(Vector3 transVec);

		static Matrix GetMMatrix(Vector3 transVec, Vector3 roteVec, Vector3 scaleVec);
};

