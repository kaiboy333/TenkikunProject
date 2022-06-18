#include "TriggerRect.h"
#include "WindowManager.h"

TriggerRect::TriggerRect(float startX, float startY, float width, float height) : Rect(startX, startY, width, height)
{
	vector<Window*> windows = WindowManager::GetWindows();

	if (windows.size() != 0) {
		for (Window* window : windows) {
			//�E�B���h�E���ɂ���Ȃ�
			if (window->IsPointIn(startX, startY)) {
				//�E�B���h�E�Ɏ��g��ǉ�
				window->AddTriggerRect(this);
				this->parentWindow = window;	//�e�E�B���h�E�ɐݒ�
				break;
			}
		}
	}
}

bool TriggerRect::CheckInput()
{
	bool isEvent = false;	//�C�x���g���N������

	//���������Ȃ��Ȃ�I���
	if (!isActive)
		return false;

	Vector3 mousePos = Input::GetMousePosition();

	//�}�E�X����������ꏊ�ɂ���Ȃ�
	if (IsPointIn(mousePos.x, mousePos.y)) {
		//���N���b�N���������u�ԂȂ�
		if (Input::GetMouseButtonDown(Input::Mouse_Left, false)) {
			MouseClickDownEvent();
			isEvent = true;
		}
		//���N���b�N�𗣂����u�ԂȂ�
		else if (Input::GetMouseButtonUp(Input::Mouse_Left, false)) {
			MouseClickUpEvent();
			isEvent = true;
		}
		//�E�N���b�N�Ȃ�
		else if (Input::GetMouseButtonDown(Input::Mouse_Right, false)) {
			MouseRightClickEvent();
			isEvent = true;
		}
		//�}�E�X������Ă邾���Ȃ�
		else {
			MouseOnEvent();
			isEvent = true;
		}
		//����Ă��锻��ɂ���
		isOn = true;
	}
	//�Ȃ��Ȃ�
	else {
		//�O��}�E�X������Ă�����
		if (isOn) {
			MouseExitEvent();
			isEvent = true;
		}
		//����Ă��Ȃ�����ɂ���
		isOn = false;
	}

	//�G���^�[���������Ȃ�
	if (Input::GetKeyDown(Input::ENTER, false)) {
		PushEnterEvent();
		isEvent = true;
	}

	return isEvent;
}

bool TriggerRect::GetIsSelected()
{
	return parentWindow->GetSelectedTriggerRect() == this;
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
