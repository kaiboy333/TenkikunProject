#include "ComponentRect.h"
#include "InspectorWindow.h"
#include "WindowManager.h"

using namespace std;

ComponentRect::ComponentRect(float startX, float startY, Component* component, int lineNum) : Rect(startX, startY, WindowManager::inspectorWindow->width, (lineNum + 2) * lineSpace + (lineNum + 1) * (float)GetFontLineSpace())
{
	this->component = component;
	this->lineNum = lineNum;
}

void ComponentRect::Draw()
{
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(0, 0, 0), FALSE);	//枠の描画

	startDrawY = startY + lineSpace;	//描画開始位置初期化

	if (component) {
		const std::type_info& type = typeid(*component);
		string componentName = type.name();	//コンポーネントの名前取得
		DrawStringF(startX, startDrawY, componentName.c_str(), GetColor(0, 0, 0));	//描画

		StartNewLine();	//改行
	}
}

void ComponentRect::StartNewLine()
{
	startDrawY += mojiHeight + lineSpace;	//文字の大きさと行間分足す
}

const float ComponentRect::lineSpace = 5;