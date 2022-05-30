#pragma once

#include "Window.h"
#include "Vector3.h"
#include "Input.h"
#include <functional>
#include <vector>


class TriggerRect
{
	public:
		TriggerRect(float x, float y, float width, float height, Window* window);

		void CheckInput();

		std::vector<std::function<void()>> mouseClickEvents;
		std::vector<std::function<void()>> mouseDoubleClickEvents;
		std::vector<std::function<void()>> mouseRightClickEvents;

	private :
		float x, y;
		float width, height;

		void MouseClickEvent();
		void MouseDoubleClickEvent();
		void MouseRightClickEvent();
};

