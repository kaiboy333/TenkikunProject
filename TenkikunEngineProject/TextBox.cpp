#include "TextBox.h"
#include "FontManager.h"
#include "Debug.h"
#include "WindowManager.h"
//#include "Window.h"

TextBox::TextBox(float startX, float startY, float width, float height, bool canChange, string text, InputType inputType, std::vector<std::string> enumStrs) : TriggerRect(startX, startY, width, height, 1)
{
	this->text = text;	//テキストセット
	this->inputType = inputType;	//入力タイプセット
	this->canChange = canChange;	//初期は変えられるか

	//EnumTypeなら
	if (this->inputType == InputType::Enum) {
		//TextButton作成
		for (int i = 0, len = (int)enumStrs.size(); i < len; i++) {
			TextButton* choice = new TextButton(this->startX, this->startY + this->height * i, this->width, this->height, 2, enumStrs[i]);
			//マウスをクリックしたら
			choice->mouseClickDownEvents.push_back(std::make_pair(choice->GetEventNo(), [this, choice, i]() {
				//textに何番目かをいれる
				this->text = std::to_string(i);
				//自身を選択対象から外す
				WindowManager::SetSelectedTriggerRect(nullptr);
				//すべて非表示にする
				for (auto enumChoice : enumChoices) {
					//反応しないようにする
					enumChoice->isActive = false;
				}
			}));
			//反応しないようにする
			choice->isActive = false;
			//リストに追加
			enumChoices.push_back(choice);
		}
	}

	//クリックしたら
	mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this, enumStrs] {
		//変更可能なら
		if (this->canChange) {
			//入力中ではないなら
			if (!GetIsSelected()) {
				//EnumTypeなら
				if (this->inputType == InputType::Enum) {
					//マウスをクリックしたら
					for (auto enumChoice : enumChoices) {
						//反応するようにする
						enumChoice->isActive = true;
					}
				}
				//それ以外なら
				else {
					ih = MakeKeyInput(MAX_LEN, FALSE, FALSE, FALSE);	//InputHandle作成
					SetActiveKeyInput(ih);	//入力を可能にする
					SetKeyInputString(this->text.c_str(), ih);	//入力中の文字の中に既にあるtextをいれる
				}
			}
			//選択中かつEnumTypeなら
			else if(GetIsSelected() && this->inputType == InputType::Enum) {
				for (auto enumChoice : enumChoices) {
					//反応しないようにする
					enumChoice->isActive = false;
				}
			}

			WindowManager::SetSelectedTriggerRect(this);	//自身を選択対象にする
		}
	}));

	//EnumType以外なら
	if (inputType != InputType::Enum) {
		//エンターを押したら
		pushEnterEvents.push_back(std::make_pair(GetEventNo(), [this]() {
			//前回のを記憶
			beforeText = this->text;

			//入力中だったなら
			if (GetIsSelected()) {
				TCHAR strBuf[MAX_LEN + 1] = {};
				GetKeyInputString(strBuf, ih);
				//空白ではないなら
				if (std::string(strBuf) != "") {
					this->text = strBuf;	//入力した文字をセット
				}

				WindowManager::SetSelectedTriggerRect(nullptr);	//自身を選択対象から外す
				DxLib::DeleteKeyInput(ih);	//InputHandle削除
			}
		}));
	}
}

void TextBox::Draw()
{
	RECT beforeDrawRect;
	//描画領域を記憶
	GetDrawArea(&beforeDrawRect);

	if (canChange) {
		//マウスが乗っていたら
		if (GetIsTopOn()) {
			//四角の描画
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
		}
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);	//枠の描画
	}

	//EnumTypeなら
	if (inputType == InputType::Enum) {
		//有効化範囲内なら
		if (activeRect) {
			//描画制限
			SetDrawArea((int)activeRect->startX, (int)activeRect->startY, (int)(activeRect->startX + activeRect->width), (int)(activeRect->startY + activeRect->height));
			//textに数字が入っているなら
			if (text != "") {
				//choiceの文字列描画
				DrawStringFToHandle(startX, startY, enumChoices[std::stoi(text)]->GetText().c_str(), GetColor(0, 0, 0), FontManager::systemFont->GetFH());
			}
			//前回の描画領域に戻す
			SetDrawArea(beforeDrawRect.left, beforeDrawRect.top, beforeDrawRect.right, beforeDrawRect.bottom);
		}
	}
	//それ以外なら
	else {
		SetKeyInputStringColor(GetColor(0, 0, 0), GetColor(50, 0, 0), GetColor(200, 200, 200), GetColor(0, 0, 50), GetColor(0, 0, 0)
			, GetColor(0, 0, 255), GetColor(0, 0, 100), GetColor(0, 0, 0), GetColor(0, 0, 0), GetColor(0, 0, 0), GetColor(0, 0, 0)
			, GetColor(200, 200, 200), GetColor(0, 0, 0), GetColor(0, 0, 200), GetColor(100, 100, 0), GetColor(0, 0, 0), GetColor(0, 0, 0)
		);

		TCHAR strBuf[MAX_LEN + 1] = "";
		GetKeyInputString(strBuf, ih);
		//入力中ではないなら
		if (!GetIsSelected()) {
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
		else {
			if (canChange) {
				DrawBoxAA(startX, startY, startX + FontManager::systemFont->GetFontWidth(strBuf), startY + FontManager::systemFont->GetFontHeight(), GetColor(30, 144, 255), TRUE);
			}
			//描画制限
			SetDrawArea(0, 0, (int)WindowManager::WIDTH, (int)WindowManager::HEIGHT);
			//DrawKeyInputModeString(0, 0);	//入力モードの描画
			DrawStringFToHandle(startX, startY, strBuf, GetColor(0, 0, 0), FontManager::systemFont->GetFH());	//入力中の文字列の描画
			//前回の描画領域に戻す
			SetDrawArea(beforeDrawRect.left, beforeDrawRect.top, beforeDrawRect.right, beforeDrawRect.bottom);
		}
	}

	//enumがあるなら描画
	if (inputType == InputType::Enum) {
		for (auto enumChoice : enumChoices) {
			enumChoice->Draw();
		}
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

void TextBox::PreparationLibrate()
{
	//enumChoicesの解放準備
	for (auto enumChoice : enumChoices) {
		//解放準備
		enumChoice->PreparationLibrate();
		//解放
		delete(enumChoice);
	}
	enumChoices.clear();

	//自身の解放準備
	TriggerRect::PreparationLibrate();
}

bool TextBox::IsTextChange()
{
	return beforeText != text;
}
