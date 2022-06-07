#include "HierarchyWindow.h"

HierarchyWindow::HierarchyWindow() : Window(0, 0, 300, 500)
{

}

void HierarchyWindow::Update()
{

}

void HierarchyWindow::Draw()
{
	//ƒoƒbƒN‚Ì•`‰æ
	Window::Draw();

	//TreeList‚Ì•`‰æ
	SceneManager::GetNowScene()->treeList->Draw();

}