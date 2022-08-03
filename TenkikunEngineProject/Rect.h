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
		bool IsPointIn2(float x, float y);	//指定座標は四角の内部か(一番右と一番下の場所は含まれない)

		std::vector<Vector3> GetPoints();

		static Rect* GetCrossRect(Rect* r1, Rect* r2);
};

