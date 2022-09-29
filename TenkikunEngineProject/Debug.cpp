#include "Debug.h"
#include "DrawComponent.h"

void Debug::Log(std::string string)
{
	OutputDebugString(std::string(string + "\n").c_str());
}

void Debug::DrawLine(Vector2 startPos, Vector2 endPos, unsigned int color)
{
	Vector2 drawStartPos = DrawComponent::GetDrawPos(startPos);
	Vector2 drawEndPos = DrawComponent::GetDrawPos(endPos);
	DrawLineAA(drawStartPos.x, drawStartPos.y, drawEndPos.x, drawEndPos.y, color);
}

void Debug::DrawPoint(Vector2 point, unsigned int color, float radious)
{
	Vector2 drawPos = DrawComponent::GetDrawPos(point);
	DrawCircleAA(drawPos.x, drawPos.y, radious, 20, color);
}
