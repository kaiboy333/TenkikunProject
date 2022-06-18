#include "HierarchyWindow.h"

HierarchyWindow::HierarchyWindow() : Window(0, 0, 300, 500)
{

}

void HierarchyWindow::Update()
{
	Window::Update();
}

void HierarchyWindow::Draw()
{
	//バックの描画
	Window::Draw();

	//TreeListの描画
	SceneManager::GetNowScene()->treeList->Draw();

}