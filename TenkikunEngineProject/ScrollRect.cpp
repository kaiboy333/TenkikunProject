#include "ScrollRect.h"
#include "MyMath.h"
#include <string>

ScrollRect::ScrollRect(float startX, float startY, float width, float height, float scrollWidth, float scrollHeight, Window* parentWindow) : TriggerRect(startX, startY, width, height, parentWindow)
{
	this->scrollWidth = scrollWidth;
	this->scrollHeight = scrollHeight;
	startScrollX = startX;
	startScrollY = startY;
	//deltaScrollX = 0;
	//deltaScrollY = 0;

	//�}�E�X�z�C�[���œ���������
	this->mouseWheelEvents.push_back([this]() {
		//�X�N���[���̍������\���\���������傫���Ȃ�
		if (this->scrollHeight > this->height) {
			//�}�E�X�z�C�[���̉�]�l���擾
			float mouseWheelRote = Input::GetMouseWheelRoteValue();
			//OutputDebugString((std::to_string(mouseWheelRote) + std::string("\n")).c_str());

			//���̂����ɑO�̃X�N���[���ʒu���L��
			float beforeStartScrollY = startScrollY;

			//�w�W�ɂȂ�X�N���[�����W�����炷
			startScrollY -= mouseWheelRote * scrollSpeed;

			//�͈͂���͂ݏo���Ȃ��悤�ɒ���
			MyMath::Clamp(startScrollY, this->startY, this->startY + this->scrollHeight - this->height);

			//����̈ړ������v�Z
			float deltaScrollY = startScrollY - beforeStartScrollY;

			for (TriggerRect* triggerRect : triggerRects) {
				//���ۂ�Y���W�����炷
				triggerRect->startY -= deltaScrollY;

				//�E�[�̈ʒu���X�N���[���̘g����O��Ă邩��isOut��ς���
				triggerRect->isOut = !IsPointIn(triggerRect->startX, triggerRect->startY);
			}
		}
	});
}

void ScrollRect::AddToScrollRect(TriggerRect* triggerRect)
{
	//���ۂɍ��W�����炷
	triggerRect->startX -= startScrollX - startX;
	triggerRect->startY -= startScrollY - startY;

	//�E�[�̈ʒu���X�N���[���̘g����O��Ă邩��isOut��ς���
	triggerRect->isOut = !IsPointIn(triggerRect->startX, triggerRect->startY);

	//���X�g�ɒǉ�
	triggerRects.push_back(triggerRect);
}

void ScrollRect::RemoveToScrollRect(TriggerRect* triggerRect)
{
	//���X�g����폜
	triggerRects.erase(remove(triggerRects.begin(), triggerRects.end(), triggerRect));
}
