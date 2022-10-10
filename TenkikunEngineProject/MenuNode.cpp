#include "MenuNode.h"
#include "FontManager.h"
#include "MenuList.h"
#include "ProjectFileManager.h"

MenuNode::MenuNode(float startX, float startY, std::string element, MenuList* parentMenuList) : TriggerRect(startX, startY, MenuList::WIDTH, FontManager::systemFont->GetFontHeight(), 100)
{
	this->element = element;
	this->parentMenuList = parentMenuList;

	//画像を取得
	arrawImage = static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\RightArrow.png"]);
	//矢印の幅を入れる
	arrawWidth = height;

	//マウスが乗った瞬間なら
	this->mouseEnterEvents.push_back(std::make_pair(GetEventNo(), [this](void) {
		if (selectedMenuNode ? selectedMenuNode->GetChildMenuList() : nullptr) {
			if (selectedMenuNode->GetParentMenuList() == this->GetParentMenuList()) {
				//前回のリスト以降をすべて見えなくするように
				std::vector<MenuList*> menuLists;
				menuLists.push_back(selectedMenuNode->GetChildMenuList());
				while (menuLists.size() != 0) {
					//先頭をポップ
					MenuList* menuList = menuLists[0];
					menuLists.erase(menuLists.begin());

					//見えなくする
					menuList->SetIsVisible(false);

					//その先にあるメニューリストを追加
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
			//見えるように
			childMenuList->SetIsVisible(true);
			//見ているメニューリストを記憶
			selectedMenuNode = this;
		}
	}));

	//マウスを押した瞬間なら
	mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		if (WindowManager::GetMenuList()) {
			//メニューリストを解除
			WindowManager::SetMenuList(nullptr);
		}
	}));
}

void MenuNode::Draw()
{
	//描画範囲を全体にする
	SetDrawArea(0, 0, (int)WindowManager::WIDTH, (int)WindowManager::HEIGHT);

	//四角の描画(塗りつぶし)
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(255, 255, 255), TRUE);
	//マウスが乗っていたら
	if (GetIsTopOn()) {
		//四角の描画
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
	}
	//文字描画
	DrawStringFToHandle(startX, startY, element.c_str(), GetColor(0, 0, 0), FontManager::systemFont->GetFH());
	//四角の描画(枠線の描画)
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

	//メニューリストが入っているなら
	if (childMenuList) {
		//矢印を描画
		if (arrawImage->GetGH()) {
			float drawCenterX = startX + width - arrawWidth / 2;
			float drawCenterY = startY + arrawWidth / 2;
			DrawRotaGraph3F(drawCenterX, drawCenterY, arrawImage->GetWidth() / 2, arrawImage->GetHeight() / 2, arrawWidth / arrawImage->GetWidth(), arrawWidth / arrawImage->GetHeight(), 0, arrawImage->GetGH(), TRUE);
		}
	}
}

void MenuNode::SetChildMenuList(MenuList* childMenuList)
{
	//見えないように
	childMenuList->SetIsVisible(false);
	//メニューリスト追加
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
