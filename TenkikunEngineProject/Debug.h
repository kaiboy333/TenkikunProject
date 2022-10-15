#pragma once
#include <string>
#include <Windows.h>
#include <debugapi.h>
#include "Vector2.h"

class Debug
{
	public:
		static void Log(std::string string);

		static void DrawLine(Vector2 startPos, Vector2 endPos, unsigned int downColor);
		static void DrawPoint(Vector2 point, unsigned int downColor, float radious = 5);
};

