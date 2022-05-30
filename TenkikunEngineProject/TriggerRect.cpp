#include "TriggerRect.h"

TriggerRect::TriggerRect(float x, float y, float width, float height, Window* window)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void TriggerRect::CheckInput()
{
	Vector3 mousePos = Input::GetMousePosition();

	float leftTopX = x - width / 2;
	float leftTopY = y - height / 2;

	//マウスが反応する場所にあるなら
	if (leftTopX <= mousePos.x && leftTopX + width >= mousePos.x
		&& leftTopY <= mousePos.y && leftTopY + height >= mousePos.y) 
	{
		if (Input::GetMouseButtonDown(Input::Mouse_Left)) {
			MouseClickEvent();
		}
		else if (Input::GetMouseButtonDown(Input::Mouse_Right)) {
			MouseRightClickEvent();
		}
	}
	//ないなら
	//イベントを起こさない
	return;
}

void TriggerRect::MouseClickEvent()
{
	for (std::function<void()> func : mouseClickEvents) {
		func();
	}
}

void TriggerRect::MouseDoubleClickEvent()
{
	for (std::function<void()> func : mouseDoubleClickEvents) {
		func();
	}
}

void TriggerRect::MouseRightClickEvent()
{
	for (std::function<void()> func : mouseRightClickEvents) {
		func();
	}
}
