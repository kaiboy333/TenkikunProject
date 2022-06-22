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

		//bool isSelected = false;	//選択されているか

		TriggerRect(float startX, float startY, float width, float height, Window* parentWindow);

		virtual void CheckInput();

		bool GetIsSelected();	//選択されているか

		std::vector<std::function<void()>> mouseClickDownEvents;
		std::vector<std::function<void()>> mouseClickUpEvents;
		std::vector<std::function<void()>> mouseDoubleClickEvents;
		std::vector<std::function<void()>> mouseRightClickEvents;
		std::vector<std::function<void()>> mouseOnEvents;
		std::vector<std::function<void()>> mouseExitEvents;

		std::vector<std::function<void()>> pushEnterEvents;

		std::vector<std::function<void()>> fileDropEvents;

	private :
		void MouseClickDownEvent();
		void MouseClickUpEvent();
		void MouseDoubleClickEvent();
		void MouseRightClickEvent();
		void MouseOnEvent();
		void MouseExitEvent();

		void PushEnterEvent();

		void FileDropEvents();
};

