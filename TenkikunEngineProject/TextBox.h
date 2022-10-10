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

		bool canChange = true;	//�ύX�\��

		TextBox(float startX, float startY, float width, float height, bool canChange, string text = "", InputType inputType = InputType::String);

		virtual void Draw();	//�`��

		void SetText(string text);
		string GetText();

		virtual void PreparationLibrate() override;

	private:
		int ih;	//�C���v�b�g�n���h��

		static const int MAX_LEN = 100;	//�ő���͕���

		string text = "";	//����
};

