#pragma once

#include "TriggerRect.h"

using namespace std;

class TextBox : public TriggerRect
{
	public:
		TextBox(float startX, float startY, float width, float height, string text = "");

		virtual void Draw();	//�`��

		void SetText(string text);
		string GetText();

	private:
		int ih;	//�C���v�b�g�n���h��

		static const int MAX_LEN = 30;	//�ő���͕���

		string text = "";	//����

		bool isInputing = false;
};

