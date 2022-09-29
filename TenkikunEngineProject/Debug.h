#pragma once
#include <string>
#include <Windows.h>
#include <debugapi.h>
#include "Vector2.h"

class Debug
{
	public:
		static void Log(std::string string);

		static void DrawLine(Vector2 startPos, Vector2 endPos, unsigned int color);
		static void DrawPoint(Vector2 point, unsigned int color, float radious = 5);
};

