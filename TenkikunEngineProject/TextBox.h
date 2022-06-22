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

		virtual void Draw();	//�`��

		void SetText(string text);
		string GetText();

	private:
		int ih;	//�C���v�b�g�n���h��

		static const int MAX_LEN = 30;	//�ő���͕���

		string text = "";	//����
};

