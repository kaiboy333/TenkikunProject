#include "HierarchyWindow.h"

HierarchyWindow::HierarchyWindow() : Window(0, 0, 300, 500)
{
	//�E�N���b�N����������
	mouseRightClickEvents.push_back(std::make_pair(GetEventNo(), [](void) {
		Vector3 mousePos = Input::GetMousePosition();

		MenuList* menuList0 = new MenuList(mousePos.x, mousePos.y, {"Create", "A", "B", "C"});
		MenuNode* menuNode0_0 = menuList0->FindNode("Create");
		//WindowManager�ɃZ�b�g
		WindowManager::SetMenuList(menuList0);

		MenuList* menuList1 = new MenuList(menuNode0_0->startX + menuNode0_0->width, menuNode0_0->startY, {"Create Empty", "Create Square", "Create Circle"});
		MenuNode* menuNode1_0 = menuList1->FindNode("Create Empty");
		menuNode1_0->mouseClickDownEvents.insert(menuNode1_0->mouseClickDownEvents.begin(), std::make_pair(menuNode1_0->GetEventNo(), []() {
			SceneManager::GetNowScene()->CreateEmpty();
		}));
		MenuNode* menuNode1_1 = menuList1->FindNode("Create Square");
		menuNode1_1->mouseClickDownEvents.insert(menuNode1_1->mouseClickDownEvents.begin(), std::make_pair(menuNode1_1->GetEventNo(), []() {
			SceneManager::GetNowScene()->CreateSquare();
		}));
		MenuNode* menuNode1_2 = menuList1->FindNode("Create Circle");
		menuNode1_2->mouseClickDownEvents.insert(menuNode1_2->mouseClickDownEvents.begin(), std::make_pair(menuNode1_2->GetEventNo(), []() {
			SceneManager::GetNowScene()->CreateCircle();
		}));
		//���j���[�m�[�h�Ƀ��j���[���X�g���Z�b�g
		menuNode0_0->SetChildMenuList(menuList1);

	}));
}

void HierarchyWindow::Update()
{
	Window::Update();
}

void HierarchyWindow::Draw()
{
	//�o�b�N�̕`��
	Window::Draw();

	//TreeList�̕`��
	SceneManager::GetNowScene()->treeList->Draw();

}