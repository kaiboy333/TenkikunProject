#include "HierarchyWindow.h"

HierarchyWindow::HierarchyWindow() : Window(300, 500, 0, 0)
{

}

void HierarchyWindow::Draw()
{
	//バックの描画
	Window::Draw();

	//TreeListの描画
	SceneManager::GetNowScene()->treeList->Draw();

}