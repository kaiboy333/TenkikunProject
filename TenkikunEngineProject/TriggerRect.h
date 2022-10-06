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
		Window* parentWindow = nullptr;	//�o�^����E�B���h�E

		bool isOn = false;	//�}�E�X�����Ƃ���true

		bool isActive = true;	//�������邩

		Rect* activeRect = nullptr;	//�L��������Ă���̈�

		float clickInterval = 0.5f;	//�N���b�N���玟�̃N���b�N�܂ł̊Ԋu
		bool isClicked = false;	//���ڃN���b�N������
		float clickTime = 0;	//�N���b�N�����Ƃ��̎���

		TriggerRect(float startX, float startY, float width, float height, Window* parentWindow, int eventNo = 0);

		void CheckInput();

		bool GetIsSelected();	//�I������Ă��邩

		int GetEventNo();	//�C�x���g�ԍ�

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

