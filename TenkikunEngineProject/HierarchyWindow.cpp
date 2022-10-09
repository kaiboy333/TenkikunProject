#include "HierarchyWindow.h"

HierarchyWindow::HierarchyWindow() : Window(0, 0, 300, 500)
{
	//右クリックを押したら
	mouseRightClickEvents.push_back(std::make_pair(0, [](void) {
		Vector3 mousePos = Input::GetMousePosition();

		MenuList* menuList0 = new MenuList(mousePos.x, mousePos.y, {"Create", "A", "B", "C"});
		MenuNode* menuNode0_0 = menuList0->FindNode("Create");
		//WindowManagerにセット
		WindowManager::SetMenuList(menuList0);

		MenuList* menuList1 = new MenuList(menuNode0_0->startX + menuNode0_0->width, menuNode0_0->startY, {"Create Empty", "Create Square", "Create Circle"});
		MenuNode* menuNode1_0 = menuList1->FindNode("Create Empty");
		menuNode1_0->onClickEvents.push_back(std::make_pair(1, []() {
			SceneManager::GetNowScene()->CreateEmpty();
		}));
		MenuNode* menuNode1_1 = menuList1->FindNode("Create Square");
		menuNode1_1->onClickEvents.push_back(std::make_pair(1, []() {
			SceneManager::GetNowScene()->CreateSquare();
		}));
		MenuNode* menuNode1_2 = menuList1->FindNode("Create Circle");
		menuNode1_2->onClickEvents.push_back(std::make_pair(1, []() {
			SceneManager::GetNowScene()->CreateCircle();
		}));
		//メニューノードにメニューリストをセット
		menuNode0_0->SetChildMenuList(menuList1);

	}));
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