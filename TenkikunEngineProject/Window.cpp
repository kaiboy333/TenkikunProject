#include "Window.h"
#include "WindowManager.h"

void Window::SetSelectedTriggerRect(TriggerRect* selectedTriggerRect)
{
	//if (this->selectedTriggerRect) {
	//	//�O��̑I�𒆂�TriggerRect��I�����Ȃ��悤�ɂ���
	//	this->selectedTriggerRect->isSelected = false;
	//}
	//if (selectedTriggerRect) {
	//	//����̑I�𒆂�TriggerRect��I������悤�ɂ���
	//	selectedTriggerRect->isSelected = true;
	//}

	//�V�����̂��Z�b�g
	this->selectedTriggerRect = selectedTriggerRect;
}

void Window::ClearSelectedTriggerRect()
{
	selectedTriggerRect = nullptr;
}

TriggerRect* Window::GetSelectedTriggerRect()
{
	return selectedTriggerRect;
}

void Window::RemoveTriggerRect(TriggerRect* triggerRect)
{
	removeTriggerRects.push_back(triggerRect);	//�������X�g�ɂ����
}

void Window::AddTriggerRect(TriggerRect* triggerRect)
{
	addTriggerRects.push_back(triggerRect);	//�ǉ����郊�X�g�ɂ����
}

Window::Window(float startX, float startY, float width, float height) : Rect(startX, startY, width, height)
{

}

void Window::Update()
{
	for (TriggerRect* removeTriggerRect : removeTriggerRects) {
		triggerRects.erase(remove(triggerRects.begin(), triggerRects.end(), removeTriggerRect));	//���ۂɍ폜
		removeTriggerRect->parentWindow = nullptr;	//TriggerRect����Q�Ƃł��Ȃ��悤��
	}
	removeTriggerRects.clear();	//�폜���X�g��������

	for (TriggerRect* addTriggerRect : addTriggerRects) {
		triggerRects.push_back(addTriggerRect);	//���ۂɒǉ�
		addTriggerRect->parentWindow = this;	//TriggerRect����Q�Ƃł���悤��
	}
	addTriggerRects.clear();	//�ǉ����X�g��������
}

void Window::EventCheck()
{
	//TriggerRect�̃C�x���g����
	for (TriggerRect* triggerRect : triggerRects) {
		triggerRect->CheckInput();	//�C�x���g�`�F�b�N
	}
}

void Window::Draw()
{
	//�`��͈͐���
	SetDrawArea((int)startX, (int)startY, (int)(startX + width - 1), (int)(startY + height - 1));
	//�����l�p��`��
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(255, 255, 255), TRUE);
	//�g����`��
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(0, 0, 0), FALSE);

}
