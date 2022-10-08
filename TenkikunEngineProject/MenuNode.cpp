#include "MenuNode.h"
#include "FontManager.h"
#include "MenuList.h"
#include "ProjectFileManager.h"

MenuNode::MenuNode(float startX, float startY, std::string element) : TriggerRect(startX, startY, MenuList::WIDTH, FontManager::systemFont->GetFontHeight())
{
	//画像を取得
	arrawImage = static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\RightArrow.png"]);
	//矢印の幅を入れる
	arrawWidth = height;
}

void MenuNode::Draw()
{
	//四角の描画(塗りつぶし)
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(255, 255, 255), TRUE);
	//四角の描画(線の描画)
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(255, 255, 255), FALSE);

	//メニューリストが入っているなら
	if (menuList) {
		//矢印を描画
		if (arrawImage->GetGH()) {
			float drawCenterX = startX + width - arrawWidth / 2;
			float drawCenterY = startY + arrawWidth / 2;
			DrawRotaGraph3F(drawCenterX, drawCenterY, arrawImage->GetWidth() / 2, arrawImage->GetHeight() / 2, arrawWidth / arrawImage->GetWidth(), arrawWidth / arrawImage->GetHeight(), 0, arrawImage->GetGH(), TRUE);
		}
	}
}
