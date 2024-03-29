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
	//描画領域を記憶
	GetDrawArea(&beforeDrawRect);

	//マウスが乗っていたら
	if (GetIsTopOn()) {
		//四角の描画
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
	}
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);	//枠の描画

	//有効化範囲内なら
	if (activeRect) {
		//描画制限
		SetDrawArea((int)activeRect->startX, (int)activeRect->startY, (int)(activeRect->startX + activeRect->width), (int)(activeRect->startY + activeRect->height));
		//変換後の文字列描画
		DrawStringFToHandle(startX, startY, text.c_str(), GetColor(0, 0, 0), FontManager::systemFont->GetFH());
		//前回の描画領域に戻す
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
    //自身の解放準備
    TriggerRect::PreparationLibrate();
}
