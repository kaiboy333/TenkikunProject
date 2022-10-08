#include "MenuNode.h"
#include "FontManager.h"
#include "MenuList.h"
#include "ProjectFileManager.h"

MenuNode::MenuNode(float startX, float startY, std::string element) : TriggerRect(startX, startY, MenuList::WIDTH, FontManager::systemFont->GetFontHeight())
{
	//‰æ‘œ‚ðŽæ“¾
	arrawImage = static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\RightArrow.png"]);
	//–îˆó‚Ì•‚ð“ü‚ê‚é
	arrawWidth = height;
}

void MenuNode::Draw()
{
	//ŽlŠp‚Ì•`‰æ(“h‚è‚Â‚Ô‚µ)
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(255, 255, 255), TRUE);
	//ŽlŠp‚Ì•`‰æ(ü‚Ì•`‰æ)
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(255, 255, 255), FALSE);

	//ƒƒjƒ…[ƒŠƒXƒg‚ª“ü‚Á‚Ä‚¢‚é‚È‚ç
	if (menuList) {
		//–îˆó‚ð•`‰æ
		if (arrawImage->GetGH()) {
			float drawCenterX = startX + width - arrawWidth / 2;
			float drawCenterY = startY + arrawWidth / 2;
			DrawRotaGraph3F(drawCenterX, drawCenterY, arrawImage->GetWidth() / 2, arrawImage->GetHeight() / 2, arrawWidth / arrawImage->GetWidth(), arrawWidth / arrawImage->GetHeight(), 0, arrawImage->GetGH(), TRUE);
		}
	}
}
