#include "TextBox.h"
//#include "Window.h"

TextBox::TextBox(float startX, float startY, float width, float height, InputType inputType, string text) : TriggerRect(startX, startY, width, height)
{
	this->text = text;	//テキストセット
	this->inputType = inputType;	//入力タイプセット

	//クリックしたら
	mouseClickDownEvents.push_back([this] {
		//入力中ではないなら
		if (!GetIsSelected()) {
			bool isTypeNum = (this->inputType == InputType::Number);

			ih = MakeKeyInput(MAX_LEN, FALSE, FALSE, FALSE);	//InputHandle作成
			SetActiveKeyInput(ih);	//入力を可能にする
			SetKeyInputString(this->text.c_str(), ih);	//入力中の文字の中に既にあるtextをいれる
			parentWindow->SetSelectedTriggerRect(this);	//自身を選択対象にする
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
				this->text = string(strBuf);	//入力した文字をセット
			}

			parentWindow->SetSelectedTriggerRect(nullptr);	//自身を選択対象から外す
			DxLib::DeleteKeyInput(ih);	//InputHandle削除
		}
	});
}

void TextBox::Draw()
{
	SetDrawArea(parentWindow->startX, parentWindow->startY, parentWindow->startX + parentWindow->width - 1, parentWindow->startY + parentWindow->height - 1);

	//マウスが乗っていたら
	if (isOn) {
		DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(220, 220, 220), TRUE);
	}
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(0, 0, 0), FALSE);	//枠の描画

	SetKeyInputStringColor(GetColor(0, 0, 0), GetColor(50, 0, 0), GetColor(200, 200, 200), GetColor(0, 0, 50), GetColor(0, 0, 0)
		, GetColor(0, 0, 255), GetColor(0, 0, 100), GetColor(0, 0, 0), GetColor(0, 0, 0), GetColor(0, 0, 0), GetColor(0, 0, 0)
		, GetColor(200, 200, 200), GetColor(0, 0, 0), GetColor(0, 0, 200), GetColor(100, 100, 0), GetColor(0, 0, 0), GetColor(0, 0, 0)
	);

	//DrawKeyInputModeString(0, 0);	//入力モードの描画

	TCHAR strBuf[MAX_LEN + 1] = "";
	GetKeyInputString(strBuf, ih);
	//入力中ではないなら
	if (!GetIsSelected()) {
		SetDrawArea(startX, startY, startX + width - 1, startY + height - 1);
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