#include "TextBox.h"
#include "FontManager.h"
#include "Debug.h"
#include "WindowManager.h"
//#include "Window.h"

TextBox::TextBox(float startX, float startY, float width, float height, bool canChange, string text, InputType inputType, std::vector<std::string> enumStrs) : TriggerRect(startX, startY, width, height, 1)
{
	this->text = text;	//�e�L�X�g�Z�b�g
	this->inputType = inputType;	//���̓^�C�v�Z�b�g
	this->canChange = canChange;	//�����͕ς����邩

	//EnumType�Ȃ�
	if (this->inputType == InputType::Enum) {
		//TextButton�쐬
		for (int i = 0, len = (int)enumStrs.size(); i < len; i++) {
			TextButton* choice = new TextButton(this->startX, this->startY + this->height * i, this->width, this->height, 2, enumStrs[i]);
			//�}�E�X���N���b�N������
			choice->mouseClickDownEvents.push_back(std::make_pair(choice->GetEventNo(), [this, choice, i]() {
				//text�ɉ��Ԗڂ��������
				this->text = std::to_string(i);
				//���g��I��Ώۂ���O��
				WindowManager::SetSelectedTriggerRect(nullptr);
				//���ׂĔ�\���ɂ���
				for (auto enumChoice : enumChoices) {
					//�������Ȃ��悤�ɂ���
					enumChoice->isActive = false;
				}
			}));
			//�������Ȃ��悤�ɂ���
			choice->isActive = false;
			//���X�g�ɒǉ�
			enumChoices.push_back(choice);
		}
	}

	//�N���b�N������
	mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this, enumStrs] {
		//�ύX�\�Ȃ�
		if (this->canChange) {
			//���͒��ł͂Ȃ��Ȃ�
			if (!GetIsSelected()) {
				//EnumType�Ȃ�
				if (this->inputType == InputType::Enum) {
					//�}�E�X���N���b�N������
					for (auto enumChoice : enumChoices) {
						//��������悤�ɂ���
						enumChoice->isActive = true;
					}
				}
				//����ȊO�Ȃ�
				else {
					ih = MakeKeyInput(MAX_LEN, FALSE, FALSE, FALSE);	//InputHandle�쐬
					SetActiveKeyInput(ih);	//���͂��\�ɂ���
					SetKeyInputString(this->text.c_str(), ih);	//���͒��̕����̒��Ɋ��ɂ���text�������
				}
			}
			//�I�𒆂���EnumType�Ȃ�
			else if(GetIsSelected() && this->inputType == InputType::Enum) {
				for (auto enumChoice : enumChoices) {
					//�������Ȃ��悤�ɂ���
					enumChoice->isActive = false;
				}
			}

			WindowManager::SetSelectedTriggerRect(this);	//���g��I��Ώۂɂ���
		}
	}));

	//EnumType�ȊO�Ȃ�
	if (inputType != InputType::Enum) {
		//�G���^�[����������
		pushEnterEvents.push_back(std::make_pair(GetEventNo(), [this]() {
			//�O��̂��L��
			beforeText = this->text;

			//���͒��������Ȃ�
			if (GetIsSelected()) {
				TCHAR strBuf[MAX_LEN + 1] = {};
				GetKeyInputString(strBuf, ih);
				//�󔒂ł͂Ȃ��Ȃ�
				if (std::string(strBuf) != "") {
					this->text = strBuf;	//���͂����������Z�b�g
				}

				WindowManager::SetSelectedTriggerRect(nullptr);	//���g��I��Ώۂ���O��
				DxLib::DeleteKeyInput(ih);	//InputHandle�폜
			}
		}));
	}
}

void TextBox::Draw()
{
	RECT beforeDrawRect;
	//�`��̈���L��
	GetDrawArea(&beforeDrawRect);

	if (canChange) {
		//�}�E�X������Ă�����
		if (GetIsTopOn()) {
			//�l�p�̕`��
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
		}
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);	//�g�̕`��
	}

	//EnumType�Ȃ�
	if (inputType == InputType::Enum) {
		//�L�����͈͓��Ȃ�
		if (activeRect) {
			//�`�搧��
			SetDrawArea((int)activeRect->startX, (int)activeRect->startY, (int)(activeRect->startX + activeRect->width), (int)(activeRect->startY + activeRect->height));
			//text�ɐ����������Ă���Ȃ�
			if (text != "") {
				//choice�̕�����`��
				DrawStringFToHandle(startX, startY, enumChoices[std::stoi(text)]->GetText().c_str(), GetColor(0, 0, 0), FontManager::systemFont->GetFH());
			}
			//�O��̕`��̈�ɖ߂�
			SetDrawArea(beforeDrawRect.left, beforeDrawRect.top, beforeDrawRect.right, beforeDrawRect.bottom);
		}
	}
	//����ȊO�Ȃ�
	else {
		SetKeyInputStringColor(GetColor(0, 0, 0), GetColor(50, 0, 0), GetColor(200, 200, 200), GetColor(0, 0, 50), GetColor(0, 0, 0)
			, GetColor(0, 0, 255), GetColor(0, 0, 100), GetColor(0, 0, 0), GetColor(0, 0, 0), GetColor(0, 0, 0), GetColor(0, 0, 0)
			, GetColor(200, 200, 200), GetColor(0, 0, 0), GetColor(0, 0, 200), GetColor(100, 100, 0), GetColor(0, 0, 0), GetColor(0, 0, 0)
		);

		TCHAR strBuf[MAX_LEN + 1] = "";
		GetKeyInputString(strBuf, ih);
		//���͒��ł͂Ȃ��Ȃ�
		if (!GetIsSelected()) {
			//�L�����͈͓��Ȃ�
			if (activeRect) {
				//�`�搧��
				SetDrawArea((int)activeRect->startX, (int)activeRect->startY, (int)(activeRect->startX + activeRect->width), (int)(activeRect->startY + activeRect->height));
				//�ϊ���̕�����`��
				DrawStringFToHandle(startX, startY, text.c_str(), GetColor(0, 0, 0), FontManager::systemFont->GetFH());
				//�O��̕`��̈�ɖ߂�
				SetDrawArea(beforeDrawRect.left, beforeDrawRect.top, beforeDrawRect.right, beforeDrawRect.bottom);
			}
		}
		else {
			if (canChange) {
				DrawBoxAA(startX, startY, startX + FontManager::systemFont->GetFontWidth(strBuf), startY + FontManager::systemFont->GetFontHeight(), GetColor(30, 144, 255), TRUE);
			}
			//�`�搧��
			SetDrawArea(0, 0, (int)WindowManager::WIDTH, (int)WindowManager::HEIGHT);
			//DrawKeyInputModeString(0, 0);	//���̓��[�h�̕`��
			DrawStringFToHandle(startX, startY, strBuf, GetColor(0, 0, 0), FontManager::systemFont->GetFH());	//���͒��̕�����̕`��
			//�O��̕`��̈�ɖ߂�
			SetDrawArea(beforeDrawRect.left, beforeDrawRect.top, beforeDrawRect.right, beforeDrawRect.bottom);
		}
	}

	//enum������Ȃ�`��
	if (inputType == InputType::Enum) {
		for (auto enumChoice : enumChoices) {
			enumChoice->Draw();
		}
	}
}

void TextBox::SetText(string text)
{
	this->text = text;
}

string TextBox::GetText()
{
	return text;
}

void TextBox::PreparationLibrate()
{
	//enumChoices�̉������
	for (auto enumChoice : enumChoices) {
		//�������
		enumChoice->PreparationLibrate();
		//���
		delete(enumChoice);
	}
	enumChoices.clear();

	//���g�̉������
	TriggerRect::PreparationLibrate();
}

bool TextBox::IsTextChange()
{
	return beforeText != text;
}
