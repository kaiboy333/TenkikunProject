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
		//Window* parentWindow = nullptr;	//�o�^����E�B���h�E

		bool isOn = false;	//�}�E�X�����Ƃ���true

		bool isActive = true;	//�������邩

		Rect* activeRect = nullptr;	//�L��������Ă���̈�

		const float CLICK_INTERVAL = GetDoubleClickTime() / 1000.0f;	//�N���b�N���玟�̃N���b�N�܂ł̊Ԋu
		bool isClicked = false;	//���ڃN���b�N������
		float clickTime = 0;	//�N���b�N�����Ƃ��̎���

		bool isClicking = false;	//�{�^������������

		TriggerRect(float startX, float startY, float width, float height, int eventNo = 0);

		void CheckInput();

		bool GetIsSelected();	//�I������Ă��邩

		int GetEventNo();	//�C�x���g�ԍ�

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

