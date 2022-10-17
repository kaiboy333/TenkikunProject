#pragma once

#include <vector>
#include "Vector3.h"
#include "Librate.h"

class Rect : public Librate
{
	public:
		float startX, startY;
		float width, height;

		Rect(float startX, float startY, float width, float height);
		Rect();

		virtual void Draw();

		bool IsPointIn(float x, float y);	//指定座標は四角の内部か
		bool IsPointIn2(float x, float y);	//指定座標は四角の内部か(一番右と一番下の場所は含まれない)

		std::vector<Vector2> GetPoints();

		static Rect* GetCrossRect(Rect* r1, Rect* r2);

		virtual void PreparationLibrate() override;

		Rect operator +(Rect& other);	//足し算
		Rect& operator +=(Rect&& other);	//足し算代入

		static bool IsHit(Rect r1, Rect r2);
};

