#pragma once

#include "Vector3.h"
#include "Input.h"
#include <functional>
#include <vector>
#include "Rect.h"


class TriggerRect : public Rect
{
	public:
		bool isOn = false;	//マウスが乗るときにtrue

		bool isActive = true;	//反応するか

		bool isSelected = false;	//選択されているか

		TriggerRect(float startX, float startY, float width, float height);

		void CheckInput();

		std::vector<std::function<void()>> mouseClickDownEvents;
		std::vector<std::function<void()>> mouseClickUpEvents;
		std::vector<std::function<void()>> mouseDoubleClickEvents;
		std::vector<std::function<void()>> mouseRightClickEvents;
		std::vector<std::function<void()>> mouseOnEvents;
		std::vector<std::function<void()>> mouseExitEvents;

		std::vector<std::function<void()>> pushEnterEvents;

	private :
		void MouseClickDownEvent();
		void MouseClickUpEvent();
		void MouseDoubleClickEvent();
		void MouseRightClickEvent();
		void MouseOnEvent();
		void MouseExitEvent();

		void PushEnterEvent();
};

