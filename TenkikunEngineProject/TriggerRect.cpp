#include "TriggerRect.h"
#include "WindowManager.h"

TriggerRect::TriggerRect(float startX, float startY, float width, float height, Window* parentWindow) : Rect(startX, startY, width, height)
{
	this->parentWindow = parentWindow;	//親ウィンドウに設定
	this->parentWindow->AddTriggerRect(this);	//ウィンドウに自身を追加
}

void TriggerRect::CheckInput()
{
	//反応させないなら終わり
	if (!isActive)
		return;

	Vector3 mousePos = Input::GetMousePosition();

	//マウスが反応する場所にあるなら
	if (IsPointIn(mousePos.x, mousePos.y)) {
		//左クリックを押した瞬間なら
		if (Input::GetMouseButtonDown(Input::Mouse_Left, false)) {
			MouseClickDownEvent();
		}
		//左クリックを離した瞬間なら
		else if (Input::GetMouseButtonUp(Input::Mouse_Left, false)) {
			MouseClickUpEvent();
		}
		//右クリックなら
		else if (Input::GetMouseButtonDown(Input::Mouse_Right, false)) {
			MouseRightClickEvent();
		}
		//マウスホイールが動いたなら
		else if(Input::GetMouseWheelRoteValue() != 0) {
			MouseWheelEvent();
		}
		//マウスが乗ってるだけなら
		MouseOnEvent();
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
	if (Input::GetKeyDown(Input::ENTER, false)) {
		PushEnterEvent();
	}

	//ファイルがドロップされたら
	if (GetDragFileNum() != 0) {
		FileDropEvents();
	}
}

bool TriggerRect::GetIsSelected()
{
	return parentWindow->GetSelectedTriggerRect() == this;
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

void TriggerRect::MouseWheelEvent()
{
	for (std::function<void()> func : mouseWheelEvents) {
		func();
	}
}

void TriggerRect::PushEnterEvent()
{
	for (std::function<void()> func : pushEnterEvents) {
		func();
	}
}

void TriggerRect::FileDropEvents()
{
	for (std::function<void()> func : fileDropEvents) {
		func();
	}
}
