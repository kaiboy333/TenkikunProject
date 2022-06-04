#pragma once

#include "Rect.h"
#include "Component.h"
#include "DxLib.h"

class ComponentRect : public Rect
{
	public:
		Component* component;

		ComponentRect(float startX, float startY, Component* component, int lineNum);

		virtual void Draw();

	protected:
		const float rightStartDrawX = startX + width * 2 / 3;	//右側の部分の描画開始位置X

		const float mojiHeight = (float)GetFontLineSpace();	//文字の高さ

		const float lineSpace = 5;	//行間

		int lineNum;	//追加で描画する行の数

		float startDrawY;	//描画開始位置Y

		void StartNewLine();	//改行するときに呼ぶ
};

