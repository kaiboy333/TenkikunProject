#include "HierarchyWindow.h"

HierarchyWindow::HierarchyWindow() : Window(0, 0, 300, 500)
{

}

void HierarchyWindow::Update()
{

}

void HierarchyWindow::Draw()
{
	//�o�b�N�̕`��
	Window::Draw();

	//TreeList�̕`��
	SceneManager::GetNowScene()->treeList->Draw();

}