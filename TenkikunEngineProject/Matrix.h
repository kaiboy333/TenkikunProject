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
		static Matrix GetMRoteX(Vector3 centerPoint, float angleX);
		static Matrix GetMRoteY(float angleY);
		static Matrix GetMRoteY(Vector3 centerPoint, float angleY);
		static Matrix GetMRoteZ(float angleZ);
		static Matrix GetMRoteZ(Vector3 centerPoint, float angleZ);

		static Matrix GetMRote(Vector3 angleVec);	//���_�𒆐S�Ɏ��g����]�����s��

		static Matrix GetMScale(Vector3 scaleVec);	//���_�𒆐S�Ɏ��g���g�債���s��

		static Matrix GetMTrans(Vector3 transVec);	//���g���ړ������s��

		static Matrix GetMMatrix(Vector3 transVec, Vector3 roteVec, Vector3 scaleVec);

		static Matrix GetMRote(Vector3 centerPoint, Vector3 angleVec);	//point�𒆐S�Ɏ��g����]�����s��

		static Matrix GetMScale(Vector3 centerPoint, Vector3 angleVec);	//point�𒆐S�Ɏ��g���g�債���s��
};

