#include "TriggerRect.h"
#include "WindowManager.h"
#include "ProjectFileManager.h"
#include "Time.h"

TriggerRect::TriggerRect(float startX, float startY, float width, float height, int eventNo) : Rect(startX, startY, width, height)
{
	WindowManager::AddTriggerRect(this);	//ウィンドウマネージャーに自身を追加
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

				//時間を測定
				float nowClickTime = Time::GetTime();
				//これが二回目のクリックかつ次のクリックまでの間隔がclickInterval以下なら
				if (isClicked && nowClickTime - clickTime <= clickInterval) {
					MouseDoubleClickEvent();
					isClicked = false;
				}
				else {
					//一度クリックした判定に
					isClicked = true;
					//時間を記憶
					clickTime = Time::GetTime();
				}
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
			//前回マウスが乗っていなかったら
			if (!isOn) {
				MouseEnterEvent();
			}

			//ファイルがドロップされたら
			if (ProjectFileManager::dragFilePathes.size() != 0) {
				FileDropEvent();
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

		//選択されていたら
		if (GetIsSelected()) {
			SelectedEvent();
		}

		//エンターを押したなら
		if (Input::GetKeyDown(Input::ENTER, false)) {
			PushEnterEvent();
		}
	}	
}

bool TriggerRect::GetIsSelected()
{
	return WindowManager::GetSelectedTriggerRect() == this;
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
		WindowManager::activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseClickUpEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : mouseClickUpEvents) {
		auto pair = std::make_pair(eventNo, func);
		WindowManager::activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseDoubleClickEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : mouseDoubleClickEvents) {
		auto pair = std::make_pair(eventNo, func);
		WindowManager::activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseRightClickEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : mouseRightClickEvents) {
		auto pair = std::make_pair(eventNo, func);
		WindowManager::activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseOnEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : mouseOnEvents) {
		auto pair = std::make_pair(eventNo, func);
		WindowManager::activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseExitEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : mouseExitEvents) {
		auto pair = std::make_pair(eventNo, func);
		WindowManager::activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseWheelEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : mouseWheelEvents) {
		auto pair = std::make_pair(eventNo, func);
		WindowManager::activeEvents.push_back(pair);
	}
}

void TriggerRect::PushEnterEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : pushEnterEvents) {
		auto pair = std::make_pair(eventNo, func);
		WindowManager::activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseEnterEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : mouseEnterEvents) {
		auto pair = std::make_pair(eventNo, func);
		WindowManager::activeEvents.push_back(pair);
	}
}

void TriggerRect::FileDropEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : fileDropEvents) {
		auto pair = std::make_pair(eventNo, func);
		WindowManager::activeEvents.push_back(pair);
	}
}

void TriggerRect::SelectedEvent()
{
	//実行可能リストに追加
	for (std::function<void()> func : selectedEvents) {
		auto pair = std::make_pair(eventNo, func);
		WindowManager::activeEvents.push_back(pair);
	}
}
