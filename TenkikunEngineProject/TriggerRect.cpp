#include "TriggerRect.h"
#include "WindowManager.h"
#include "ProjectFileManager.h"

TriggerRect::TriggerRect(float startX, float startY, float width, float height, Window* parentWindow, int eventNo) : Rect(startX, startY, width, height)
{
	this->parentWindow = parentWindow;
	this->parentWindow->AddTriggerRect(this);	//�E�B���h�E�Ɏ��g��ǉ�
	this->eventNo = eventNo;

	activeRect = new Rect(startX, startY, width, height);
}

void TriggerRect::CheckInput()
{
	//���������Ȃ��Ȃ�I���
	if (!isActive)
		return;

	//�L���ł���̈悪null�łȂ��Ȃ�
	if (activeRect) {
		//�����������Ȃ��Ȃ�
		if (activeRect->width == 0 || activeRect->height == 0)
			//�I���
			return;

		Vector3 mousePos = Input::GetMousePosition();

		//�}�E�X����������ꏊ�ɂ���Ȃ�
		if (activeRect->IsPointIn2(mousePos.x, mousePos.y)) {
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
			else if (Input::GetMouseWheelRoteValue() != 0) {
				MouseWheelEvent();
			}

			//�}�E�X������Ă邾���Ȃ�
			MouseOnEvent();

			//�t�@�C�����h���b�v���ꂽ��
			if (ProjectFileManager::dragFilePathes.size() != 0) {
				FileDropEvents();
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
		if (Input::GetKeyDown(Input::ENTER, false)) {
			PushEnterEvent();
		}
	}	
}

bool TriggerRect::GetIsSelected()
{
	return parentWindow->GetSelectedTriggerRect() == this;
}

int TriggerRect::GetEventNo()
{
	return eventNo;
}

void TriggerRect::MouseClickDownEvent()
{
	//���s�\���X�g�ɒǉ�
	for (std::function<void()> func : mouseClickDownEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseClickUpEvent()
{
	//���s�\���X�g�ɒǉ�
	for (std::function<void()> func : mouseClickUpEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseDoubleClickEvent()
{
	//���s�\���X�g�ɒǉ�
	for (std::function<void()> func : mouseDoubleClickEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseRightClickEvent()
{
	//���s�\���X�g�ɒǉ�
	for (std::function<void()> func : mouseRightClickEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseOnEvent()
{
	//���s�\���X�g�ɒǉ�
	for (std::function<void()> func : mouseOnEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseExitEvent()
{
	//���s�\���X�g�ɒǉ�
	for (std::function<void()> func : mouseExitEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::MouseWheelEvent()
{
	//���s�\���X�g�ɒǉ�
	for (std::function<void()> func : mouseWheelEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::PushEnterEvent()
{
	//���s�\���X�g�ɒǉ�
	for (std::function<void()> func : pushEnterEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}

void TriggerRect::FileDropEvents()
{
	//���s�\���X�g�ɒǉ�
	for (std::function<void()> func : fileDropEvents) {
		auto pair = std::make_pair(eventNo, func);
		parentWindow->activeEvents.push_back(pair);
	}
}
