#pragma once

#include "TriggerRect.h"
#include "TextButton.h"

using namespace std;

class TextBox : public TriggerRect
{
	public:
		enum class InputType {
			String,
			Number,
			Enum,
		};

		InputType inputType;

		bool canChange = true;	//�ύX�\��

		std::vector<TextButton*> enumChoices;	//enum�̑I��������

		TextBox(float startX, float startY, float width, float height, bool canChange, string text = "", InputType inputType = InputType::String, std::vector<std::string> enumStrs = {});

		virtual void Draw();	//�`��

		void SetText(string text);
		string GetText();

		virtual void PreparationLibrate() override;

		bool IsTextChange();	//�������ς�����΂��肩

	private:
		int ih;	//�C���v�b�g�n���h��

		static const int MAX_LEN = 100;	//�ő���͕���

		string text = "";	//����

		std::string beforeText = "";	//��O�̕���
};

