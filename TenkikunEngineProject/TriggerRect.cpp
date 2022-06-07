#include "TriggerRect.h"
#include "WindowManager.h"

TriggerRect::TriggerRect(float startX, float startY, float width, float height) : Rect(startX, startY, width, height)
{
	WindowManager::AddTriggerRect(this);
}

void TriggerRect::CheckInput()
{
	//反応させないなら終わり
	if (!isActive)
		return;

	Vector3 mousePos = Input::GetMousePosition();

	//マウスが反応する場所にあるなら
	if (startX <= mousePos.x && startX + width >= mousePos.x
		&& startY <= mousePos.y && startY + height >= mousePos.y) {
		//左クリックを押した瞬間なら
		if (Input::GetMouseButtonDown(Input::Mouse_Left)) {
			MouseClickDownEvent();
		}
		//左クリックを離した瞬間なら
		else if (Input::GetMouseButtonUp(Input::Mouse_Left)) {
			MouseClickUpEvent();
		}
		//右クリックなら
		else if (Input::GetMouseButtonDown(Input::Mouse_Right)) {
			MouseRightClickEvent();
		}
		//マウスが乗ってるだけなら
		else {
			MouseOnEvent();
		}
		//乗っている判定にする
		isOn = true;
	}
	//ないなら
	else {
		//前回マウスが乗っていたら
		if (isOn) {
			MouseExitEvent();
		}
		//乗っていない判定にする
		isOn = false;
	}

	//エンターを押したなら
	if (Input::GetKeyDown(Input::ENTER)) {
		PushEnterEvent();
	}
}

void TriggerRect::MouseClickDownEvent()
{
	for (std::function<void()> func : mouseClickDownEvents) {
		func();
	}
}

void TriggerRect::MouseClickUpEvent()
{
	for (std::function<void()> func : mouseClickUpEvents) {
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

void TriggerRect::MouseOnEvent()
{
	for (std::function<void()> func : mouseOnEvents) {
		func();
	}
}

void TriggerRect::MouseExitEvent()
{
	for (std::function<void()> func : mouseExitEvents) {
		func();
	}
}

void TriggerRect::PushEnterEvent()
{
	for (std::function<void()> func : pushEnterEvents) {
		func();
	}
}
