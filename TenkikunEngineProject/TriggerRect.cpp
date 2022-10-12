#include "TriggerRect.h"
#include "WindowManager.h"
#include "ProjectFileManager.h"
#include "Time.h"

TriggerRect::TriggerRect(float startX, float startY, float width, float height, int eventNo) : Rect(startX, startY, width, height)
{
	WindowManager::AddTriggerRect(this);	//ウィンドウマネージャーに自身を追加
	this->eventNo = eventNo;

	activeRect = new Rect(startX, startY, width, height);

	//マウスが入ったら
	this->mouseEnterEvents.push_back(std::make_pair(GetEventNo(), [this](void) {
		isTopOn = true;
	}));
	//マウスが出たら
	this->mouseExitEvents.push_back(std::make_pair(GetEventNo(), [this](void) {
		isTopOn = false;
	}));
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
				AddToActiveEvents(mouseClickDownEvents);

				//時間を測定
				float nowClickTime = Time::GetTime();
				//これが二回目のクリックかつ次のクリックまでの間隔がclickInterval以下なら
				if (isClicked && nowClickTime - clickTime <= CLICK_INTERVAL) {
					AddToActiveEvents(mouseDoubleClickEvents);
					isClicked = false;
				}
				else {
					//一度クリックした判定に
					isClicked = true;
					//時間を記憶
					clickTime = Time::GetTime();
				}

				//マウスが乗っていたら
				if (isOn) {
					isClicking = true;
				}
			}
			//左クリックを離した瞬間なら
			else if (Input::GetMouseButtonUp(Input::Mouse_Left, false)) {
				AddToActiveEvents(mouseClickUpEvents);

				//前にクリックしていたなら
				if (isClicking) {
					AddToActiveEvents(onClickEvents);
				}
			}
			//右クリックなら
			else if (Input::GetMouseButtonDown(Input::Mouse_Right, false)) {
				AddToActiveEvents(mouseRightClickEvents);
			}
			//マウスホイールが動いたなら
			else if (Input::GetMouseWheelRoteValue() != 0) {
				AddToActiveEvents(mouseWheelEvents);
			}

			//マウスが乗ってるだけなら
			AddToActiveEvents(mouseOnEvents);
			//前回マウスが乗っていなかったら
			if (!isOn) {
				AddToActiveEvents(mouseEnterEvents);
			}

			//ファイルがドロップされたら
			if (ProjectFileManager::dragFilePathes.size() != 0) {
				AddToActiveEvents(fileDropEvents);
			}
			//乗っている判定にする
			isOn = true;
		}
		//ないなら
		else {
			//前回マウスが乗っていたら
			if (isOn) {
				AddToActiveEvents(mouseExitEvents);

				//クリック判定をなしに
				isClicking = false;
			}
			//乗っていない判定にする
			isOn = false;
		}

		//エンターを押したなら
		if (Input::GetKeyDown(Input::ENTER, false)) {
			AddToActiveEvents(pushEnterEvents);
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

bool TriggerRect::GetIsTopOn()
{
	return isTopOn;
}

void TriggerRect::AddToActiveEvents(std::vector<std::pair<int, std::function<void()>>> pairs)
{
	//実行可能リストに追加
	for (std::pair<int, std::function<void()>> pair : pairs) {
		WindowManager::activeEvents.push_back(pair);
	}
}

void TriggerRect::PreparationLibrate()
{
	//WindowManagerから削除
	WindowManager::RemoveTriggerRect(this);

	//Rectの解放準備
	if (activeRect) {
		activeRect->PreparationLibrate();
		//解放
		delete(activeRect);
		activeRect = nullptr;
	}

	//自身の解放準備
	Rect::PreparationLibrate();
}
