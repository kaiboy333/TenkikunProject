#pragma once

#include "Rect.h"
#include "Component.h"
#include "DxLib.h"
#include "WindowManager.h"
#include "FontManager.h"

class TextRect;
class ComponentRect : public Rect
{
	public:
		Component* component;

		TextRect* nameRect = nullptr;

		ComponentRect(float startX, float startY, Component* component, int lineNum);

		virtual void Update() = 0;

		virtual void Draw();

		//virtual void RemoveAllTriggerRect() = 0;	//自身が作ったTriggerRectをすべて削除

		virtual void PreparationLibrate() override;

	protected:
		float rightStartDrawX = startX + width * 2 / 5;	//右側の部分の描画開始位置X

		const float mojiHeight = FontManager::systemFont->GetFontHeight();	//文字の高さ

		static const float lineSpace;	//行間

		int lineNum;	//追加で描画する行の数

		float startDrawY;	//描画開始位置Y

		void StartNewLine();	//改行するときに呼ぶ
		float GetRightRectX(Rect* rect);	//Rectの右端のXを取得
};

