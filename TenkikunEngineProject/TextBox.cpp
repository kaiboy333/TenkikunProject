#include "TextBox.h"
#include "FontManager.h"
#include "Debug.h"
//#include "Window.h"

TextBox::TextBox(float startX, float startY, float width, float height, Window* parentWindow, bool canChange, string text, InputType inputType) : TriggerRect(startX, startY, width, height, parentWindow)
{
	this->text = text;	//テキストセット
	this->inputType = inputType;	//入力タイプセット
	this->canChange = canChange;	//初期は変えられるか

	//クリックしたら
	mouseClickDownEvents.push_back([this] {
		//変更可能なら
		if (this->canChange) {
			//入力中ではないなら
			if (!GetIsSelected()) {
				bool isTypeNum = (this->inputType == InputType::Number);

				ih = MakeKeyInput(MAX_LEN, FALSE, FALSE, FALSE);	//InputHandle作成
				SetActiveKeyInput(ih);	//入力を可能にする
				SetKeyInputString(this->text.c_str(), ih);	//入力中の文字の中に既にあるtextをいれる
				this->parentWindow->SetSelectedTriggerRect(this);	//自身を選択対象にする
			}
		}
	});

	//エンターを押したら
	pushEnterEvents.push_back([this]() {
		//入力中だったなら
		if (GetIsSelected()) {
			TCHAR strBuf[MAX_LEN + 1] = {};
			GetKeyInputString(strBuf, ih);
			//空白ではないなら
			if (strBuf != "") {
				this->text = strBuf;	//入力した文字をセット
			}

			this->parentWindow->SetSelectedTriggerRect(nullptr);	//自身を選択対象から外す
			DxLib::DeleteKeyInput(ih);	//InputHandle削除
		}
	});
}

void TextBox::Draw()
{
	RECT beforeDrawRect;
	//描画領域を記憶
	GetDrawArea(&beforeDrawRect);

	if (canChange) {
		//マウスが乗っていたら
		if (isOn) {
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(220, 220, 220), TRUE);
		}
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);	//枠の描画
	}

	SetKeyInputStringColor(GetColor(0, 0, 0), GetColor(50, 0, 0), GetColor(200, 200, 200), GetColor(0, 0, 50), GetColor(0, 0, 0)
		, GetColor(0, 0, 255), GetColor(0, 0, 100), GetColor(0, 0, 0), GetColor(0, 0, 0), GetColor(0, 0, 0), GetColor(0, 0, 0)
		, GetColor(200, 200, 200), GetColor(0, 0, 0), GetColor(0, 0, 200), GetColor(100, 100, 0), GetColor(0, 0, 0), GetColor(0, 0, 0)
	);

	//DrawKeyInputModeString(0, 0);	//入力モードの描画

	TCHAR strBuf[MAX_LEN + 1] = "";
	GetKeyInputString(strBuf, ih);
	//入力中ではないなら
	if (!GetIsSelected()) {
		//有効化範囲内なら
		if (activeRect) {
			//描画制限
			SetDrawArea(activeRect->startX, activeRect->startY, activeRect->startX + activeRect->width, activeRect->startY + activeRect->height);
			//変換後の文字列描画
			DrawStringFToHandle(startX, startY, text.c_str(), GetColor(0, 0, 0), FontManager::systemFont->GetFH());
			//前回の描画領域に戻す
			SetDrawArea(beforeDrawRect.left, beforeDrawRect.top, beforeDrawRect.right, beforeDrawRect.bottom);
		}
	}
	else {
		if (canChange) {
			DrawBoxAA(startX, startY, startX + FontManager::systemFont->GetFontWidth(strBuf), startY + FontManager::systemFont->GetFontHeight(), GetColor(200, 200, 200), TRUE);
		}
		DrawStringFToHandle(startX, startY, strBuf, GetColor(0, 0, 0), FontManager::systemFont->GetFH());	//入力中の文字列の描画
	}
}

void TextBox::SetText(string text)
{
	this->text = text;
}

string TextBox::GetText()
{
	return text;
}