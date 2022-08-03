#pragma once

#include <vector>
#include "Vector3.h"

class Rect
{
	public:
		float startX, startY;
		float width, height;

		Rect(float startX, float startY, float width, float height);

		virtual void Draw();

		bool IsPointIn(float x, float y);	//�w����W�͎l�p�̓�����
		bool IsPointIn2(float x, float y);	//�w����W�͎l�p�̓�����(��ԉE�ƈ�ԉ��̏ꏊ�͊܂܂�Ȃ�)

		std::vector<Vector3> GetPoints();

		static Rect* GetCrossRect(Rect* r1, Rect* r2);
};

