#pragma once

#include "TriggerRect.h"

using namespace std;

class TextBox : public TriggerRect
{
	public:
		enum class InputType {
			String,
			Number,
		};

		InputType inputType;

		TextBox(float startX, float startY, float width, float height, Window* parentWindow, InputType inputType = InputType::String, string text = "");

		virtual void Draw();	//描画

		void SetText(string text);
		string GetText();

	private:
		int ih;	//インプットハンドル

		static const int MAX_LEN = 30;	//最大入力文字

		string text = "";	//文字
};

