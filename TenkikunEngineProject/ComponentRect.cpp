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
	//画像のアルファ値設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);	//枠の描画

	nameRect->Draw();	//コンポーネントの名前描画
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