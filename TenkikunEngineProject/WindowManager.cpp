#include "WindowManager.h"

void WindowManager::Draw()
{
	gameWindow->Draw();	//�Q�[����ʂ̕`��
	hierarchyWindow->Draw();	//�q�G�����L�[�E�B���h�E�̕`��
	inspectorWindow->Draw();	//�C���X�y�N�^�[�E�B���h�E�̕`��
}

void WindowManager::Update()
{
	gameWindow->Update();	//�Q�[����ʂ̍X�V
	hierarchyWindow->Update();	//�q�G�����L�[�E�B���h�E�̍X�V
	inspectorWindow->Update();	//�C���X�y�N�^�[�E�B���h�E�̍X�V

	//TriggerRect�̃C�x���g����
	for (TriggerRect* triggerRect : triggerRects) {
		triggerRect->CheckInput();	//�C�x���g�`�F�b�N
	}
	for (TriggerRect* removeTriggerRect : removeTriggerRects) {
		triggerRects.erase(remove(triggerRects.begin(), triggerRects.end(), removeTriggerRect));	//���ۂɍ폜
	}
	removeTriggerRects.clear();	//�폜���X�g��������
	for (TriggerRect* addTriggerRect : addTriggerRects) {
		triggerRects.push_back(addTriggerRect);	//���ۂɒǉ�
	}
	addTriggerRects.clear();	//�ǉ����X�g��������
}

void WindowManager::SetSelectedTriggerRect(TriggerRect* selectedTriggerRect)
{
	if (WindowManager::selectedTriggerRect) {
		//�O��̑I�𒆂�TriggerRect��I�����Ȃ��悤�ɂ���
		WindowManager::selectedTriggerRect->isSelected = false;
	}
	if (selectedTriggerRect) {
		//����̑I�𒆂�TriggerRect��I������悤�ɂ���
		selectedTriggerRect->isSelected = true;
	}

	//�V�����̂��Z�b�g
	WindowManager::selectedTriggerRect = selectedTriggerRect;
}

TriggerRect* WindowManager::GetSelectedTriggerRect()
{
	return selectedTriggerRect;
}

void WindowManager::AddTriggerRect(TriggerRect* triggerRect) {
	WindowManager::addTriggerRects.push_back(triggerRect);	//�ǉ����郊�X�g�ɂ����
}

void WindowManager::RemoveTriggerRect(TriggerRect* triggerRect) {
	WindowManager::removeTriggerRects.push_back(triggerRect);	//�������X�g�ɂ����
}

std::vector<TriggerRect*> WindowManager::triggerRects;
std::vector<TriggerRect*> WindowManager::removeTriggerRects;
std::vector<TriggerRect*> WindowManager::addTriggerRects;

TriggerRect* WindowManager::selectedTriggerRect;

GameWindow* WindowManager::gameWindow = new GameWindow();
HierarchyWindow* WindowManager::hierarchyWindow = new HierarchyWindow();
InspectorWindow* WindowManager::inspectorWindow = new InspectorWindow();

