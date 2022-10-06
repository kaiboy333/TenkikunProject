#pragma once

#include "Vector3.h"
#include "Input.h"
#include <functional>
#include <vector>
#include "Rect.h"
#include "Window.h"

class Window;
class TriggerRect : public Rect
{
	public:
		Window* parentWindow = nullptr;	//登録するウィンドウ

		bool isOn = false;	//マウスが乗るときにtrue

		bool isActive = true;	//反応するか

		Rect* activeRect = nullptr;	//有効化されている領域

		float clickInterval = 0.5f;	//クリックから次のクリックまでの間隔
		bool isClicked = false;	//一回目クリックしたか
		float clickTime = 0;	//クリックしたときの時間

		TriggerRect(float startX, float startY, float width, float height, Window* parentWindow, int eventNo = 0);

		void CheckInput();

		bool GetIsSelected();	//選択されているか

		int GetEventNo();	//イベント番号

		std::vector<std::function<void()>> mouseClickDownEvents;
		std::vector<std::function<void()>> mouseClickUpEvents;
		std::vector<std::function<void()>> mouseDoubleClickEvents;
		std::vector<std::function<void()>> mouseRightClickEvents;
		std::vector<std::function<void()>> mouseOnEvents;
		std::vector<std::function<void()>> mouseEnterEvents;
		std::vector<std::function<void()>> mouseExitEvents;
		std::vector<std::function<void()>> mouseWheelEvents;

		std::vector<std::function<void()>> selectedEvents;

		std::vector<std::function<void()>> pushEnterEvents;

		std::vector<std::function<void()>> fileDropEvents;

	private :
		int eventNo;

		void MouseClickDownEvent();
		void MouseClickUpEvent();
		void MouseDoubleClickEvent();
		void MouseRightClickEvent();
		void MouseOnEvent();
		void MouseEnterEvent();
		void MouseExitEvent();
		void MouseWheelEvent();

		void SelectedEvent();

		void PushEnterEvent();

		void FileDropEvent();
};

