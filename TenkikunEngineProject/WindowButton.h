#pragma once

#include "TriggerRect.h"
#include <functional>
#include "Image.h"

using namespace std;

class WindowButton : public TriggerRect
{
	public:
		//ボタンが押された時に呼ぶ関数たち
		vector<function<void()>> onClickEvents;

		Image* image = nullptr;	//画像

		WindowButton(float startX, float startY, float width, float height);

		void Draw();

	private:
		//ボタンを押したか
		bool isClicking = false;

		void OnClickEvent();	//ボタンが押された時に呼ぶイベント

};

