#include "HierarchyWindow.h"

HierarchyWindow::HierarchyWindow() : Window(300, 500, 0, 0)
{

}

void HierarchyWindow::Draw()
{
	//ƒoƒbƒN‚Ì•`‰æ
	Window::Draw();

	//TreeList‚Ì•`‰æ
	SceneManager::GetNowScene()->treeList->Draw();

}