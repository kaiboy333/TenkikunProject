#include "TriggerRect.h"
#include "WindowManager.h"

TriggerRect::TriggerRect(float startX, float startY, float width, float height, Window* parentWindow) : Rect(startX, startY, width, height)
{
	this->parentWindow = parentWindow;	//�e�E�B���h�E�ɐݒ�
	this->parentWindow->AddTriggerRect(this);	//�E�B���h�E�Ɏ��g��ǉ�
}

void TriggerRect::CheckInput()
{
	//���������Ȃ��Ȃ�I���
	if (!isActive)
		return;

	Vector3 mousePos = Input::GetMousePosition();

	//�}�E�X����������ꏊ�ɂ���Ȃ�
	if (IsPointIn(mousePos.x, mousePos.y)) {
		//���N���b�N���������u�ԂȂ�
		if (Input::GetMouseButtonDown(Input::Mouse_Left, false)) {
			MouseClickDownEvent();
		}
		//���N���b�N�𗣂����u�ԂȂ�
		else if (Input::GetMouseButtonUp(Input::Mouse_Left, false)) {
			MouseClickUpEvent();
		}
		//�E�N���b�N�Ȃ�
		else if (Input::GetMouseButtonDown(Input::Mouse_Right, false)) {
			MouseRightClickEvent();
		}
		//�}�E�X�z�C�[�����������Ȃ�
		else if(Input::GetMouseWheelRoteValue() != 0) {
			MouseWheelEvent();
		}
		//�}�E�X������Ă邾���Ȃ�
		MouseOnEvent();
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
	if (Input::GetKeyDown(Input::ENTER, false)) {
		PushEnterEvent();
	}

	//�t�@�C�����h���b�v���ꂽ��
	if (GetDragFileNum() != 0) {
		FileDropEvents();
	}
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

void TriggerRect::MouseWheelEvent()
{
	for (std::function<void()> func : mouseWheelEvents) {
		func();
	}
}

void TriggerRect::PushEnterEvent()
{
	for (std::function<void()> func : pushEnterEvents) {
		func();
	}
}

void TriggerRect::FileDropEvents()
{
	for (std::function<void()> func : fileDropEvents) {
		func();
	}
}
