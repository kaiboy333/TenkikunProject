#include "ComponentRect.h"
#include "InspectorWindow.h"
#include "WindowManager.h"
#include "TextRect.h"

using namespace std;

ComponentRect::ComponentRect(float startX, float startY, Component* component, int lineNum) : Rect(startX, startY, WindowManager::inspectorWindow->width, (lineNum + 2) * lineSpace + (lineNum + 1) * FontManager::systemFont->GetFontHeight())
{
	this->component = component;
	this->lineNum = lineNum;

	startDrawY = startY + lineSpace;	//�`��J�n�ʒuY������

	nameRect = new TextRect(startX, startDrawY, typeid(*component).name());

	StartNewLine();	//���s
}

void ComponentRect::Draw()
{
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);	//�g�̕`��

	nameRect->Draw();	//�R���|�[�l���g�̖��O�`��

	//�e�L�X�g�`��
	for (TextRect* textRect : textRects) {
		textRect->Draw();
	}
	//�e�L�X�g�{�b�N�X�`��
	for (TextBox* textBox : textBoxes) {
		textBox->Draw();
	}
	//SelectRect
	for (SelectRect* selectRect : selectRects) {
		selectRect->Draw();
	}
	//CheckButton
	for (CheckButton* checkButton : checkButtons) {
		checkButton->Draw();
	}
}

void ComponentRect::PreparationLibrate()
{
	//TextRect�̉������
	nameRect->PreparationLibrate();
	//���
	delete(nameRect);
	nameRect = nullptr;

	//�e�L�X�g�{�b�N�X
	for (TextBox* textBox : textBoxes) {
		//�e�L�X�g�{�b�N�X�̉������
		textBox->PreparationLibrate();
		//���
		delete(textBox);
		textBox = nullptr;
	}
	textBoxes.clear();

	//TextRect
	for (TextRect* textRect : textRects) {
		//TextRect�̉������
		textRect->PreparationLibrate();
		//���
		delete(textRect);
		textRect = nullptr;
	}
	textRects.clear();

	//SelectRect
	for (SelectRect* selectRect : selectRects) {
		//SelectRect�̉������
		selectRect->PreparationLibrate();
		//���
		delete(selectRect);
		selectRect = nullptr;
	}
	selectRects.clear();

	//CheckButton
	for (CheckButton* checkButton : checkButtons) {
		//CheckButton�̉������
		checkButton->PreparationLibrate();
		//���
		delete(checkButton);
		checkButton = nullptr;
	}
	checkButtons.clear();

	//���g�̉������
	Rect::PreparationLibrate();
}

void ComponentRect::StartNewLine()
{
	startDrawY += mojiHeight + lineSpace;	//�����̑傫���ƍs�ԕ�����
}

float ComponentRect::GetRightRectX(Rect* rect)
{
	return rect->startX + rect->width;
}

const float ComponentRect::lineSpace = 5;