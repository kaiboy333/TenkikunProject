#pragma once
class Rect
{
	public:
		float startX, startY;
		float width, height;

		Rect(float startX, float startY, float width, float height);

		virtual void Draw();

		bool IsPointIn(float x, float y);	//w’èÀ•W‚ÍlŠp‚Ì“à•”‚©
};

