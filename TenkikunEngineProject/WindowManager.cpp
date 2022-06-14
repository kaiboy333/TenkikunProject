#include "WindowManager.h"

void WindowManager::Draw()
{
	gameWindow->Draw();	//�Q�[����ʂ̕`��
	hierarchyWindow->Draw();	//�q�G�����L�[�E�B���h�E�̕`��
	inspectorWindow->Draw();	//�C���X�y�N�^�[�E�B���h�E�̕`��
}

void WindowManager::Update()
{
	for (Window* window : GetWindows()) {
		window->Update();

		window->EventUpdate();
	}
}

vector<Window*> WindowManager::GetWindows()
{
	vector<Window*> windows;

	if (gameWindow && hierarchyWindow && inspectorWindow) {
		windows.push_back(gameWindow);
		windows.push_back(hierarchyWindow);
		windows.push_back(inspectorWindow);
	}

	return windows;
}

//void WindowManager::SetSelectedTriggerRect(TriggerRect* selectedTriggerRect)
//{
//	if (WindowManager::selectedTriggerRect) {
//		//�O��̑I�𒆂�TriggerRect��I�����Ȃ��悤�ɂ���
//		WindowManager::selectedTriggerRect->isSelected = false;
//	}
//	if (selectedTriggerRect) {
//		//����̑I�𒆂�TriggerRect��I������悤�ɂ���
//		selectedTriggerRect->isSelected = true;
//	}
//
//	//�V�����̂��Z�b�g
//	WindowManager::selectedTriggerRect = selectedTriggerRect;
//}

//TriggerRect* WindowManager::GetSelectedTriggerRect()
//{
//	return selectedTriggerRect;
//}
//
//void WindowManager::AddTriggerRect(TriggerRect* triggerRect) {
//	WindowManager::addTriggerRects.push_back(triggerRect);	//�ǉ����郊�X�g�ɂ����
//}
//
//void WindowManager::RemoveTriggerRect(TriggerRect* triggerRect) {
//	WindowManager::removeTriggerRects.push_back(triggerRect);	//�������X�g�ɂ����
//}
//
//std::vector<TriggerRect*> WindowManager::triggerRects;
//std::vector<TriggerRect*> WindowManager::removeTriggerRects;
//std::vector<TriggerRect*> WindowManager::addTriggerRects;
//
//TriggerRect* WindowManager::selectedTriggerRect;

GameWindow* WindowManager::gameWindow = new GameWindow();
HierarchyWindow* WindowManager::hierarchyWindow = new HierarchyWindow();
InspectorWindow* WindowManager::inspectorWindow = new InspectorWindow();

Window* WindowManager::activeTrigggerWindow = WindowManager::gameWindow;	//�����̓Q�[�����

