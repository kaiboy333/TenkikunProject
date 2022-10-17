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

		bool IsPointIn(float x, float y);	//�w����W�͎l�p�̓�����
		bool IsPointIn2(float x, float y);	//�w����W�͎l�p�̓�����(��ԉE�ƈ�ԉ��̏ꏊ�͊܂܂�Ȃ�)

		std::vector<Vector2> GetPoints();

		static Rect* GetCrossRect(Rect* r1, Rect* r2);

		virtual void PreparationLibrate() override;

		Rect operator +(Rect& other);	//�����Z
		Rect& operator +=(Rect&& other);	//�����Z���

		static bool IsHit(Rect r1, Rect r2);
};

