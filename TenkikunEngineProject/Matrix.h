#pragma once
#include "Vector3.h"
#include <math.h>
#include "MyMath.h"

class Matrix
{
	public:
		float m[4][4] = {};

		Matrix operator*(const Matrix& other) const;	//�s��̊|���Z
		Vector3 operator*(const Vector3& other) const;	//�s���Vector3�̊|���Z
		static Matrix GetUnit();	//�P�ʍs���Ԃ�

		static Matrix GetMRoteX(float angleX);
		static Matrix GetMRoteX(const Vector3& centerPoint, float angleX);
		static Matrix GetMRoteY(float angleY);
		static Matrix GetMRoteY(const Vector3& centerPoint, float angleY);
		static Matrix GetMRoteZ(float angleZ);
		static Matrix GetMRoteZ(const Vector3& centerPoint, float angleZ);

		static Matrix GetMRote(const Vector3& angleVec);	//���_�𒆐S�Ɏ��g����]�����s��

		static Matrix GetMScale(const Vector3& scaleVec);	//���_�𒆐S�Ɏ��g���g�債���s��

		static Matrix GetMTrans(const Vector3& transVec);	//���g���ړ������s��

		static Matrix GetMMatrix(const Vector3& transVec, const Vector3& roteVec, const Vector3& scaleVec);

		static Matrix GetMRote(const Vector3& centerPoint, const Vector3& angleVec);	//point�𒆐S�Ɏ��g����]�����s��

		static Matrix GetMScale(const Vector3& centerPoint, const Vector3& angleVec);	//point�𒆐S�Ɏ��g���g�債���s��
};

