#include "MenuNode.h"
#include "FontManager.h"
#include "MenuList.h"
#include "ProjectFileManager.h"

MenuNode::MenuNode(float startX, float startY, std::string element, MenuList* parentMenuList) : TriggerRect(startX, startY, MenuList::WIDTH, FontManager::systemFont->GetFontHeight(), 100)
{
	this->element = element;
	this->parentMenuList = parentMenuList;

	//�摜���擾
	arrawImage = static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\RightArrow.png"]);
	//���̕�������
	arrawWidth = height;

	//�}�E�X��������u�ԂȂ�
	this->mouseEnterEvents.push_back(std::make_pair(GetEventNo(), [this](void) {
		if (selectedMenuNode ? selectedMenuNode->GetChildMenuList() : nullptr) {
			if (selectedMenuNode->GetParentMenuList() == this->GetParentMenuList()) {
				//�O��̃��X�g�ȍ~�����ׂČ����Ȃ�����悤��
				std::vector<MenuList*> menuLists;
				menuLists.push_back(selectedMenuNode->GetChildMenuList());
				while (menuLists.size() != 0) {
					//�擪���|�b�v
					MenuList* menuList = menuLists[0];
					menuLists.erase(menuLists.begin());

					//�����Ȃ�����
					menuList->SetIsVisible(false);

					//���̐�ɂ��郁�j���[���X�g��ǉ�
					for (MenuNode* menuNode : menuList->menuNodes) {
						if (menuNode->GetChildMenuList()) {
							menuLists.push_back(menuNode->GetChildMenuList());
						}
					}
				}

			}
		}
		MenuList* childMenuList = this->GetChildMenuList();
		if (childMenuList) {
			//������悤��
			childMenuList->SetIsVisible(true);
			//���Ă��郁�j���[���X�g���L��
			selectedMenuNode = this;
		}
	}));

	//�}�E�X���������u�ԂȂ�
	mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		if (WindowManager::GetMenuList()) {
			//���j���[���X�g������
			WindowManager::SetMenuList(nullptr);
		}
	}));
}

void MenuNode::Draw()
{
	//�`��͈͂�S�̂ɂ���
	SetDrawArea(0, 0, (int)WindowManager::WIDTH, (int)WindowManager::HEIGHT);

	//�l�p�̕`��(�h��Ԃ�)
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(255, 255, 255), TRUE);
	//�}�E�X������Ă�����
	if (GetIsTopOn()) {
		//�l�p�̕`��
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
	}
	//�����`��
	DrawStringFToHandle(startX, startY, element.c_str(), GetColor(0, 0, 0), FontManager::systemFont->GetFH());
	//�l�p�̕`��(�g���̕`��)
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

	//���j���[���X�g�������Ă���Ȃ�
	if (childMenuList) {
		//����`��
		if (arrawImage->GetGH()) {
			float drawCenterX = startX + width - arrawWidth / 2;
			float drawCenterY = startY + arrawWidth / 2;
			DrawRotaGraph3F(drawCenterX, drawCenterY, arrawImage->GetWidth() / 2, arrawImage->GetHeight() / 2, arrawWidth / arrawImage->GetWidth(), arrawWidth / arrawImage->GetHeight(), 0, arrawImage->GetGH(), TRUE);
		}
	}
}

void MenuNode::SetChildMenuList(MenuList* childMenuList)
{
	//�����Ȃ��悤��
	childMenuList->SetIsVisible(false);
	//���j���[���X�g�ǉ�
	this->childMenuList = childMenuList;
}

MenuList* MenuNode::GetChildMenuList()
{
	return childMenuList;
}

MenuList* MenuNode::GetParentMenuList() {
	return parentMenuList;
}


MenuNode* MenuNode::selectedMenuNode = nullptr;
