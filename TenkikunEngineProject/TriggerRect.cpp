#include "TriggerRect.h"
#include "WindowManager.h"

TriggerRect::TriggerRect(float startX, float startY, float width, float height) : Rect(startX, startY, width, height)
{
	WindowManager::triggerRects.push_back(this);
}

void TriggerRect::CheckInput()
{
	//���������Ȃ��Ȃ�I���
	if (!isActive)
		return;

	Vector3 mousePos = Input::GetMousePosition();

	//�}�E�X����������ꏊ�ɂ���Ȃ�
	if (startX <= mousePos.x && startX + width >= mousePos.x
		&& startY <= mousePos.y && startY + height >= mousePos.y) {
		//���N���b�N�Ȃ�
		if (Input::GetMouseButtonDown(Input::Mouse_Left)) {
			MouseClickEvent();
		}
		//�E�N���b�N�Ȃ�
		else if (Input::GetMouseButtonDown(Input::Mouse_Right)) {
			MouseRightClickEvent();
		}
		//�}�E�X������Ă邾���Ȃ�
		else {
			MouseOnEvent();
		}
		//����Ă��锻��ɂ���
		isOn = true;
	}
	//�Ȃ��Ȃ�
	else {
		//�O��}�E�X������Ă�����
		if (isOn) {
			MouseExitEvent();
		}
		//����Ă��Ȃ�����ɂ���
		isOn = false;
	}
}

void TriggerRect::MouseClickEvent()
{
	for (std::function<void()> func : mouseClickEvents) {
		func();
	}
}

void TriggerRect::MouseDoubleClickEvent()
{
	for (std::function<void()> func : mouseDoubleClickEvents) {
		func();
	}
}

void TriggerRect::MouseRightClickEvent()
{
	for (std::function<void()> func : mouseRightClickEvents) {
		func();
	}
}

void TriggerRect::MouseOnEvent()
{
	for (std::function<void()> func : mouseOnEvents) {
		func();
	}
}

void TriggerRect::MouseExitEvent()
{
	for (std::function<void()> func : mouseExitEvents) {
		func();
	}
}
