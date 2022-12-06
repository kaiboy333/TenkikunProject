#include "Debug.h"
#include "DrawComponent.h"

void Debug::Log(std::string string)
{
	OutputDebugString(std::string(string + "\n").c_str());
}

void Debug::DrawLine(const Vector2& startPos, const Vector2& endPos, const unsigned int downColor)
{
	Vector2 drawStartPos = DrawComponent::GetDrawPos(startPos);
	Vector2 drawEndPos = DrawComponent::GetDrawPos(endPos);
	DrawLineAA(drawStartPos.x, drawStartPos.y, drawEndPos.x, drawEndPos.y, downColor);
}

void Debug::DrawPoint(const Vector2& point, const unsigned int downColor, const float radious)
{
	Vector2 drawPos = DrawComponent::GetDrawPos(point);
	DrawCircleAA(drawPos.x, drawPos.y, radious, 20, downColor);
}
