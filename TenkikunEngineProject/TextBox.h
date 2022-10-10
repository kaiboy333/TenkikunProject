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

		bool canChange = true;	//変更可能か

		TextBox(float startX, float startY, float width, float height, bool canChange, string text = "", InputType inputType = InputType::String);

		virtual void Draw();	//描画

		void SetText(string text);
		string GetText();

		virtual void PreparationLibrate() override;

	private:
		int ih;	//インプットハンドル

		static const int MAX_LEN = 100;	//最大入力文字

		string text = "";	//文字
};

