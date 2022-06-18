#include "ComponentRect.h"
#include "InspectorWindow.h"
#include "WindowManager.h"
#include "TextRect.h"

using namespace std;

ComponentRect::ComponentRect(float startX, float startY, Component* component, int lineNum) : Rect(startX, startY, WindowManager::inspectorWindow->width, (lineNum + 2) * lineSpace + (lineNum + 1) * (float)GetFontLineSpace())
{
	this->component = component;
	this->lineNum = lineNum;

	startDrawY = startY + lineSpace;	//�`��J�n�ʒuY������

	nameRect = new TextRect(startX, startDrawY, typeid(*component).name());

	StartNewLine();	//���s
}

void ComponentRect::Draw()
{
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(0, 0, 0), FALSE);	//�g�̕`��

	nameRect->Draw();	//�R���|�[�l���g�̖��O�`��
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