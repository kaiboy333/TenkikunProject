#pragma once

#include "Vector3.h"
#include "Input.h"
#include <functional>
#include <vector>
#include "Rect.h"


class TriggerRect : public Rect
{
	public:
		bool isOn = false;	//�}�E�X�����Ƃ���true

		bool isActive = true;	//�������邩

		bool isSelected = false;	//�I������Ă��邩

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

