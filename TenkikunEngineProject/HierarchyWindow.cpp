#include "HierarchyWindow.h"

HierarchyWindow::HierarchyWindow() : Window(300, 500, 0, 0)
{

}

void HierarchyWindow::Draw()
{
	//�o�b�N�̕`��
	Window::Draw();

	//TreeList�̕`��
	SceneManager::GetNowScene()->treeList->Draw();

}