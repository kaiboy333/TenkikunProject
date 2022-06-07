#include "TriggerRect.h"
#include "WindowManager.h"

TriggerRect::TriggerRect(float startX, float startY, float width, float height) : Rect(startX, startY, width, height)
{
	WindowManager::AddTriggerRect(this);
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
		//���N���b�N���������u�ԂȂ�
		if (Input::GetMouseButtonDown(Input::Mouse_Left)) {
			MouseClickDownEvent();
		}
		//���N���b�N�𗣂����u�ԂȂ�
		else if (Input::GetMouseButtonUp(Input::Mouse_Left)) {
			MouseClickUpEvent();
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

	//�G���^�[���������Ȃ�
	if (Input::GetKeyDown(Input::ENTER)) {
		PushEnterEvent();
	}
}

void TriggerRect::MouseClickDownEvent()
{
	for (std::function<void()> func : mouseClickDownEvents) {
		func();
	}
}

void TriggerRect::MouseClickUpEvent()
{
	for (std::function<void()> func : mouseClickUpEvents) {
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

void TriggerRect::PushEnterEvent()
{
	for (std::function<void()> func : pushEnterEvents) {
		func();
	}
}
