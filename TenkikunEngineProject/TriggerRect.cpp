#include "TriggerRect.h"
#include "WindowManager.h"
#include "ProjectFileManager.h"
#include "Time.h"

TriggerRect::TriggerRect(float startX, float startY, float width, float height, int eventNo) : Rect(startX, startY, width, height)
{
	WindowManager::AddTriggerRect(this);	//�E�B���h�E�}�l�[�W���[�Ɏ��g��ǉ�
	this->eventNo = eventNo;

	activeRect = new Rect(startX, startY, width, height);

	//�}�E�X����������
	this->mouseEnterEvents.push_back(std::make_pair(GetEventNo(), [this](void) {
		isTopOn = true;
	}));
	//�}�E�X���o����
	this->mouseExitEvents.push_back(std::make_pair(GetEventNo(), [this](void) {
		isTopOn = false;
	}));
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
				AddToActiveEvents(mouseClickDownEvents);

				//���Ԃ𑪒�
				float nowClickTime = Time::GetTime();
				//���ꂪ���ڂ̃N���b�N�����̃N���b�N�܂ł̊Ԋu��clickInterval�ȉ��Ȃ�
				if (isClicked && nowClickTime - clickTime <= CLICK_INTERVAL) {
					AddToActiveEvents(mouseDoubleClickEvents);
					isClicked = false;
				}
				else {
					//��x�N���b�N���������
					isClicked = true;
					//���Ԃ��L��
					clickTime = Time::GetTime();
				}

				//�}�E�X������Ă�����
				if (isOn) {
					isClicking = true;
				}
			}
			//���N���b�N�𗣂����u�ԂȂ�
			else if (Input::GetMouseButtonUp(Input::Mouse_Left, false)) {
				AddToActiveEvents(mouseClickUpEvents);

				//�O�ɃN���b�N���Ă����Ȃ�
				if (isClicking) {
					AddToActiveEvents(onClickEvents);
				}
			}
			//�E�N���b�N�Ȃ�
			else if (Input::GetMouseButtonDown(Input::Mouse_Right, false)) {
				AddToActiveEvents(mouseRightClickEvents);
			}
			//�}�E�X�z�C�[�����������Ȃ�
			else if (Input::GetMouseWheelRoteValue() != 0) {
				AddToActiveEvents(mouseWheelEvents);
			}

			//�}�E�X������Ă邾���Ȃ�
			AddToActiveEvents(mouseOnEvents);
			//�O��}�E�X������Ă��Ȃ�������
			if (!isOn) {
				AddToActiveEvents(mouseEnterEvents);
			}

			//�t�@�C�����h���b�v���ꂽ��
			if (ProjectFileManager::dragFilePathes.size() != 0) {
				AddToActiveEvents(fileDropEvents);
			}
			//����Ă��锻��ɂ���
			isOn = true;
		}
		//�Ȃ��Ȃ�
		else {
			//�O��}�E�X������Ă�����
			if (isOn) {
				AddToActiveEvents(mouseExitEvents);

				//�N���b�N������Ȃ���
				isClicking = false;
			}
			//����Ă��Ȃ�����ɂ���
			isOn = false;
		}

		//�G���^�[���������Ȃ�
		if (Input::GetKeyDown(Input::ENTER, false)) {
			AddToActiveEvents(pushEnterEvents);
		}
	}
}

bool TriggerRect::GetIsSelected()
{
	return WindowManager::GetSelectedTriggerRect() == this;
}

int TriggerRect::GetEventNo()
{
	return eventNo;
}

bool TriggerRect::GetIsTopOn()
{
	return isTopOn;
}

void TriggerRect::AddToActiveEvents(std::vector<std::pair<int, std::function<void()>>> pairs)
{
	//���s�\���X�g�ɒǉ�
	for (std::pair<int, std::function<void()>> pair : pairs) {
		WindowManager::activeEvents.push_back(pair);
	}
}

void TriggerRect::PreparationLibrate()
{
	//WindowManager����폜
	WindowManager::RemoveTriggerRect(this);

	//Rect�̉������
	if (activeRect) {
		activeRect->PreparationLibrate();
		//���
		delete(activeRect);
		activeRect = nullptr;
	}

	//���g�̉������
	Rect::PreparationLibrate();
}
