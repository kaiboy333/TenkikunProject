#include "TextBox.h"

TextBox::TextBox(float startX, float startY, float width, float height, string text) : TriggerRect(startX, startY, width, height)
{
	this->text = text;	//テキストセット

	//クリックしたら
	mouseClickDownEvents.push_back([this] {
		//InitKeyInput();	//入力初期化
		ih = MakeKeyInput(MAX_LEN, FALSE, FALSE, FALSE);	//InputHandle作成
		SetActiveKeyInput(ih);	//入力を可能にする
		SetKeyInputString(this->text.c_str(), ih);	//入力中の文字の中に既にあるtextをいれる
		isInputing = true;	//入力状態フラグオン
	});

	//エンターを押したら
	pushEnterEvents.push_back([this]() {
		//入力中だったなら
		if (isInputing) {
			TCHAR strBuf[MAX_LEN + 1] = "";
			GetKeyInputString(strBuf, ih);
			//空白ではないなら
			if (strBuf != "") {
				this->text = string(strBuf);	//入力した文字をセット
			}
			else {

			}

			isInputing = false;	//入力状態フラグオフ
			InitKeyInput();	//入力を不可に(初期化)
		}
	});
}

void TextBox::Draw()
{
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(0, 0, 0), FALSE);	//枠の描画

	SetKeyInputStringColor(GetColor(0, 0, 0), GetColor(50, 0, 0), GetColor(200, 200, 200), GetColor(0, 0, 50), GetColor(100, 0, 0)
		, GetColor(200, 200, 200), GetColor(0, 0, 100), GetColor(0, 0, 0), GetColor(200, 200, 200), GetColor(150, 0, 0), GetColor(150, 0, 0)
		, GetColor(200, 0, 0), GetColor(0, 0, 0), GetColor(0, 0, 200), GetColor(100, 100, 0), GetColor(0, 0, 0), GetColor(0, 0, 0)
	);

	//DrawKeyInputModeString(0, 0);	//入力モードの描画

	TCHAR strBuf[MAX_LEN + 1] = "";
	GetKeyInputString(strBuf, ih);
	//SetDrawArea(startX, startY, startX + width - 1, startY + height - 1);
	//入力中ではないなら
	if (!isInputing) {
		DrawStringF(startX, startY, text.c_str(), GetColor(0, 0, 0));	//変換後の文字列描画
	}
	else {
		DrawBoxAA(startX, startY, startX + (float)GetDrawStringWidth(strBuf, strlen(strBuf)), startY + (float)GetFontLineSpace(), GetColor(200, 200, 200), TRUE);
		DrawKeyInputString((int)startX, (int)startY, ih);	//入力中の文字列の描画
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