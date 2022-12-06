#pragma once
#include <string>
#include <Windows.h>
#include <debugapi.h>
#include "Vector2.h"

class Debug
{
	public:
		static void Log(std::string string);

		static void DrawLine(const Vector2& startPos, const Vector2& endPos, const unsigned int downColor);
		static void DrawPoint(const Vector2& point, const unsigned int downColor, const float radious);
};

