#include "WindowManager.h"

void WindowManager::Draw()
{
	gameWindow->Draw();	//�Q�[����ʂ̕`��
	hierarchyWindow->Draw();	//�q�G�����L�[�E�B���h�E�̕`��
}

GameWindow* WindowManager::gameWindow = new GameWindow();
HierarchyWindow* WindowManager::hierarchyWindow = new HierarchyWindow();

