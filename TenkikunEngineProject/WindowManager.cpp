#include "WindowManager.h"

void WindowManager::Draw()
{
	gameWindow->Draw();	//�Q�[����ʂ̕`��
	hierarchyWindow->Draw();	//�q�G�����L�[�E�B���h�E�̕`��
	inspectorWindow->Draw();	//�C���X�y�N�^�[�E�B���h�E�̕`��
}

void WindowManager::Update()
{
	//TriggerRect�̃C�x���g����
	for (TriggerRect* triggerRect : triggerRects) {
		triggerRect->CheckInput();
	}
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

std::vector<TriggerRect*> WindowManager::triggerRects;
TriggerRect* WindowManager::selectedTriggerRect;

GameWindow* WindowManager::gameWindow = new GameWindow();
HierarchyWindow* WindowManager::hierarchyWindow = new HierarchyWindow();
InspectorWindow* WindowManager::inspectorWindow = new InspectorWindow();

