#include "TriggerRect.h"
#include "WindowManager.h"
#include "ProjectFileManager.h"

TriggerRect::TriggerRect(float startX, float startY, float width, float height, Window* parentWindow, int eventNo) : Rect(startX, startY, width, height)
{
	this->parentWindow = parentWindow;
	this->parentWindow->AddTriggerRect(this);	//ウィンドウに自身を追加
	this->eventNo = eventNo;

	activeRect = new Rect(startX, startY, width, height);
}

void TriggerRect::CheckInput()
{
	//反応させないなら終わり
	if (!isActive)
		return;

	//有効である領域がnullでないなら
	if (activeRect) {
		//幅か高さがないなら
		if (activeRect->width == 0 || activeRect->height == 0)
			//終わり
			return;

		Vector3 mousePos = Input::GetMousePosition();

		//マウスが反応する場所にあるなら
		if (activeRect->IsPointIn2(mousePos.x, mousePos.y)) {
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
			else if (Input::GetMouseWheelRoteValue() != 0) {
				MouseWheelEvent();
			}

			//マウスが乗ってるだけなら
			MouseOnEvent();

			//ファイルがドロップされたら
			if (ProjectFileManager::dragFilePathes.size() != 0) {
				FileDropEvents();
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
		if (Input::GetKeyDown(Input::ENTER, false)) {
			PushEnterEvent();
		}
	}	
}

bool TriggerRect::GetIsSelected()
{
	return parentWindow->GetSelectedTriggerRect() == this;
}

int TriggerRect::GetEventNo()
{
	return eventNo;
}

void TriggerRect::MouseClickDownEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : mouseClickDownEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseClickUpEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : mouseClickUpEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseDoubleClickEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : mouseDoubleClickEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseRightClickEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : mouseRightClickEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseOnEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : mouseOnEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseExitEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : mouseExitEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseWheelEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : mouseWheelEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::PushEnterEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : pushEnterEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::FileDropEvents()
{
	//実行可能リストに追加
	for (std::function<void()> func : fileDropEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}
