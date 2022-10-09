#include "ScrollRect.h"
#include "MyMath.h"
#include <string>

ScrollRect::ScrollRect(float startX, float startY, float width, float height, float scrollWidth, float scrollHeight) : TriggerRect(startX, startY, width, height)
{
	this->scrollWidth = scrollWidth;
	this->scrollHeight = scrollHeight;
	startScrollX = startX;
	startScrollY = startY;

	//�}�E�X�z�C�[���œ���������
	this->mouseWheelEvents.push_back(std::make_pair(0, [this]() {
		//�X�N���[���̍������\���\���������傫���Ȃ�
		if (this->scrollHeight > this->height) {
			//�}�E�X�z�C�[���̉�]�l���擾
			float mouseWheelRote = Input::GetMouseWheelRoteValue();
			//OutputDebugString((std::to_string(mouseWheelRote) + std::string("\n")).c_str());

			//���̂����ɑO�̃X�N���[���ʒu���L��
			float beforeStartScrollY = startScrollY;

			//�w�W�ɂȂ�X�N���[�����W�����炷
			startScrollY += mouseWheelRote * scrollSpeed;

			//�͈͂���͂ݏo���Ȃ��悤�ɒ���
			startScrollY = MyMath::Clamp(startScrollY, this->startY - (this->scrollHeight - this->height), this->startY);

			//����̈ړ������v�Z
			float deltaScrollY = startScrollY - beforeStartScrollY;

			for (TriggerRect* triggerRect : triggerRects) {
				//���ۂ�Y���W�����炷
				triggerRect->startY += deltaScrollY;
			}

			ScrollUpdate();	//�L�����X�V
		}
	}));
}

void ScrollRect::AddToScrollRect(TriggerRect* triggerRect)
{
	//���ۂɍ��W�����炷
	triggerRect->startX += startScrollX - startX;
	triggerRect->startY += startScrollY - startY;

	//TriggerRect�̗L���͈͂̓X�N���[���̂��Ԃ�͈͂ł���
	triggerRect->activeRect = Rect::GetCrossRect(triggerRect, this);

	//���X�g�ɒǉ�
	triggerRects.push_back(triggerRect);
}

void ScrollRect::RemoveToScrollRect(TriggerRect* triggerRect)
{
	//���X�g����폜
	triggerRects.erase(remove(triggerRects.begin(), triggerRects.end(), triggerRect));

	triggerRect->activeRect = nullptr;	//������
}

void ScrollRect::ScrollUpdate()
{
	//�X�N���[���̍������\���\���������傫���Ȃ�
	if (this->scrollHeight > this->height) {
		float deltaY = startY + height - (startScrollY + scrollHeight);
		//�X�N���[���̒�ɋ󔒂��ł��Ă��܂��Ă����疄�܂�悤�ɉ��ɂ��炷
		if (deltaY > 0) {
			//�X�N���[���ʒu��ς���
			startScrollY += deltaY;

			for (TriggerRect* triggerRect : triggerRects) {
				//���ۂ�Y���W�����炷
				triggerRect->startY += deltaY;
			}
		}
	}

	for (TriggerRect* triggerRect : triggerRects) {
		//TriggerRect�̗L���͈͂̓X�N���[���̂��Ԃ�͈͂ł���
		triggerRect->activeRect = Rect::GetCrossRect(triggerRect, this);
	}
}

void ScrollRect::InitScrollPos()
{
	startScrollX = startX;
	startScrollY = startY;
}
