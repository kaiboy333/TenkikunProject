#include "ProjectWindow.h"
#include "TreeNode.h"

ProjectWindow::ProjectWindow() : Window(0, 500, 1000, 300)
{
	treeList = new TreeList(this, true, "Project");
	treeList->Add(new TreeNode("Scenes", treeList), treeList->GetRoot());
}

void ProjectWindow::Update()
{
	Window::Update();
}

void ProjectWindow::Draw()
{
	Window::Draw();

	if (treeList) {
		treeList->Draw();
	}
}
