#include "TextButton.h"
#include "FontManager.h"

TextButton::TextButton(float startX, float startY, float width, float height, int eventNo, std::string text) : TriggerRect(startX, startY, width, height, eventNo)
{
    this->text = text;
}

void TextButton::Draw()
{
    if (!isActive)
        return;

	RECT beforeDrawRect;
	//•`‰æ—Ìˆæ‚ğ‹L‰¯
	GetDrawArea(&beforeDrawRect);

	//ƒ}ƒEƒX‚ªæ‚Á‚Ä‚¢‚½‚ç
	if (GetIsTopOn()) {
		//lŠp‚Ì•`‰æ
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
	}
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);	//˜g‚Ì•`‰æ

	//—LŒø‰»”ÍˆÍ“à‚È‚ç
	if (activeRect) {
		//•`‰æ§ŒÀ
		SetDrawArea((int)activeRect->startX, (int)activeRect->startY, (int)(activeRect->startX + activeRect->width), (int)(activeRect->startY + activeRect->height));
		//•ÏŠ·Œã‚Ì•¶š—ñ•`‰æ
		DrawStringFToHandle(startX, startY, text.c_str(), GetColor(0, 0, 0), FontManager::systemFont->GetFH());
		//‘O‰ñ‚Ì•`‰æ—Ìˆæ‚É–ß‚·
		SetDrawArea(beforeDrawRect.left, beforeDrawRect.top, beforeDrawRect.right, beforeDrawRect.bottom);
	}
}

void TextButton::SetText(std::string text)
{
    this->text = text;
}

std::string TextButton::GetText()
{
    return text;
}

void TextButton::PreparationLibrate()
{
    //©g‚Ì‰ğ•ú€”õ
    TriggerRect::PreparationLibrate();
}
