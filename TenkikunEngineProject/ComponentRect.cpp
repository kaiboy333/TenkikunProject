#include "ComponentRect.h"
#include "InspectorWindow.h"
#include "WindowManager.h"
#include "TextRect.h"

using namespace std;

ComponentRect::ComponentRect(float startX, float startY, Component* component, int lineNum) : Rect(startX, startY, WindowManager::inspectorWindow->width, (lineNum + 2) * lineSpace + (lineNum + 1) * FontManager::systemFont->GetFontHeight())
{
	this->component = component;
	this->lineNum = lineNum;

	startDrawY = startY + lineSpace;	//描画開始位置Y初期化

	nameRect = new TextRect(startX, startDrawY, typeid(*component).name());

	StartNewLine();	//改行
}

void ComponentRect::Draw()
{
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);	//枠の描画

	nameRect->Draw();	//コンポーネントの名前描画

	//テキスト描画
	for (TextRect* textRect : textRects) {
		textRect->Draw();
	}
	//テキストボックス描画
	for (TextBox* textBox : textBoxes) {
		textBox->Draw();
	}
	//SelectRect
	for (SelectRect* selectRect : selectRects) {
		selectRect->Draw();
	}
	//CheckButton
	for (CheckButton* checkButton : checkButtons) {
		checkButton->Draw();
	}
}

void ComponentRect::PreparationLibrate()
{
	//TextRectの解放準備
	nameRect->PreparationLibrate();
	//解放
	delete(nameRect);
	nameRect = nullptr;

	//テキストボックス
	for (TextBox* textBox : textBoxes) {
		//テキストボックスの解放準備
		textBox->PreparationLibrate();
		//解放
		delete(textBox);
		textBox = nullptr;
	}
	textBoxes.clear();

	//TextRect
	for (TextRect* textRect : textRects) {
		//TextRectの解放準備
		textRect->PreparationLibrate();
		//解放
		delete(textRect);
		textRect = nullptr;
	}
	textRects.clear();

	//SelectRect
	for (SelectRect* selectRect : selectRects) {
		//SelectRectの解放準備
		selectRect->PreparationLibrate();
		//解放
		delete(selectRect);
		selectRect = nullptr;
	}
	selectRects.clear();

	//CheckButton
	for (CheckButton* checkButton : checkButtons) {
		//CheckButtonの解放準備
		checkButton->PreparationLibrate();
		//解放
		delete(checkButton);
		checkButton = nullptr;
	}
	checkButtons.clear();

	//自身の解放準備
	Rect::PreparationLibrate();
}

void ComponentRect::StartNewLine()
{
	startDrawY += mojiHeight + lineSpace;	//文字の大きさと行間分足す
}

float ComponentRect::GetRightRectX(Rect* rect)
{
	return rect->startX + rect->width;
}

const float ComponentRect::lineSpace = 5;