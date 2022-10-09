#include "MenuList.h"
#include "FontManager.h"

MenuList::MenuList(float startX, float startY, std::vector<std::string> elements) : Rect(startX, startY, WIDTH, FontManager::systemFont->GetFontHeight() * elements.size())
{
	//���j���[�m�[�h���쐬�A�ǉ�
	for (int i = 0, len = (int)elements.size(); i < len; i++) {
		MenuNode* menuNode = new MenuNode(startX, startY + i * FontManager::systemFont->GetFontHeight(), elements[i], this);
		this->menuNodes.push_back(menuNode);
	}
}

void MenuList::SetIsVisible(bool isVisible)
{
	this->isVisible = isVisible;

	for (MenuNode* menuNode : menuNodes) {
		menuNode->isActive = isVisible;
	}
}

void MenuList::Draw()
{
	std::vector<MenuList*> menuLists;
	menuLists.push_back(this);

	while ((int)menuLists.size() != 0) {
		MenuList* menuList = menuLists[0];
		menuLists.erase(menuLists.begin());

		if (menuList->isVisible) {
			for (MenuNode* menuNode : menuList->menuNodes) {
				//�`��
				menuNode->Draw();
				//���j���[���X�g������Ȃ�
				if (menuNode->GetChildMenuList()) {
					//�ǉ�
					menuLists.push_back(menuNode->GetChildMenuList());
				}
			}
		}
		else {
			return;
		}
	}

}

MenuNode* MenuList::FindNode(std::string element)
{
	for (MenuNode* menuNode : menuNodes) {
		if (menuNode->element == element) {
			return menuNode;
		}
	}

	return nullptr;
}
