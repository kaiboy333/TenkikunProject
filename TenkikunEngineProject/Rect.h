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

		bool IsPointIn(float x, float y);	//指定座標は四角の内部か

		std::vector<Vector3> GetPoints();

		static Rect* GetCrossRect(Rect* r1, Rect* r2);
};

