#pragma once
#include "Vector3.h"
#include <math.h>
#include "MyMath.h"

class Matrix
{
	public:
		float m[4][4] = {};

		Matrix operator*(const Matrix& other) const;	//行列の掛け算
		Vector3 operator*(const Vector3& other) const;	//行列とVector3の掛け算
		static Matrix GetUnit();	//単位行列を返す

		static Matrix GetMRoteX(float angleX);
		static Matrix GetMRoteX(const Vector3& centerPoint, float angleX);
		static Matrix GetMRoteY(float angleY);
		static Matrix GetMRoteY(const Vector3& centerPoint, float angleY);
		static Matrix GetMRoteZ(float angleZ);
		static Matrix GetMRoteZ(const Vector3& centerPoint, float angleZ);

		static Matrix GetMRote(const Vector3& angleVec);	//原点を中心に自身を回転した行列

		static Matrix GetMScale(const Vector3& scaleVec);	//原点を中心に自身を拡大した行列

		static Matrix GetMTrans(const Vector3& transVec);	//自身を移動した行列

		static Matrix GetMMatrix(const Vector3& transVec, const Vector3& roteVec, const Vector3& scaleVec);

		static Matrix GetMRote(const Vector3& centerPoint, const Vector3& angleVec);	//pointを中心に自身を回転した行列

		static Matrix GetMScale(const Vector3& centerPoint, const Vector3& angleVec);	//pointを中心に自身を拡大した行列
};

