#pragma once

#include "Vector3.h"
#include "Input.h"
#include <functional>
#include <vector>
#include "Rect.h"
//#include "Window.h"

//class Window;
class TriggerRect : public Rect
{
	public:
		//Window* parentWindow = nullptr;	//登録するウィンドウ

		bool isOn = false;	//マウスが乗るときにtrue

		bool isActive = true;	//反応するか

		Rect* activeRect = nullptr;	//有効化されている領域

		const float CLICK_INTERVAL = GetDoubleClickTime() / 1000.0f;	//クリックから次のクリックまでの間隔
		bool isClicked = false;	//一回目クリックしたか
		float clickTime = 0;	//クリックしたときの時間

		bool isClicking = false;	//ボタンを押したか

		TriggerRect(float startX, float startY, float width, float height, int eventNo = 0);

		void CheckInput();

		bool GetIsSelected();	//選択されているか

		int GetEventNo();	//イベント番号

		std::vector<std::pair<int, std::function<void()>>> mouseClickDownEvents;
		std::vector<std::pair<int, std::function<void()>>> mouseClickUpEvents;
		std::vector<std::pair<int, std::function<void()>>> onClickEvents;
		std::vector<std::pair<int, std::function<void()>>> mouseDoubleClickEvents;
		std::vector<std::pair<int, std::function<void()>>> mouseRightClickEvents;
		std::vector<std::pair<int, std::function<void()>>> mouseOnEvents;
		std::vector<std::pair<int, std::function<void()>>> mouseEnterEvents;
		std::vector<std::pair<int, std::function<void()>>> mouseExitEvents;
		std::vector<std::pair<int, std::function<void()>>> mouseWheelEvents;

		std::vector<std::pair<int, std::function<void()>>> selectedEvents;

		std::vector<std::pair<int, std::function<void()>>> pushEnterEvents;

		std::vector<std::pair<int, std::function<void()>>> fileDropEvents;

	private :
		int eventNo;

		void AddToActiveEvents(std::vector<std::pair<int, std::function<void()>>> pairs);
};

