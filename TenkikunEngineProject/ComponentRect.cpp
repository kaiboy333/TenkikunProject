#include "ComponentRect.h"
#include "InspectorWindow.h"
#include "WindowManager.h"

using namespace std;

ComponentRect::ComponentRect(float startX, float startY, Component* component, int lineNum) : Rect(startX, startY, WindowManager::inspectorWindow->width, (lineNum + 2) * lineSpace + (lineNum + 1) * (float)GetFontLineSpace())
{
	this->component = component;
	this->lineNum = lineNum;
}

void ComponentRect::Draw()
{
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(0, 0, 0), FALSE);	//�g�̕`��

	startDrawY = startY + lineSpace;	//�`��J�n�ʒu������

	if (component) {
		const std::type_info& type = typeid(*component);
		string componentName = type.name();	//�R���|�[�l���g�̖��O�擾
		DrawStringF(startX, startDrawY, componentName.c_str(), GetColor(0, 0, 0));	//�`��

		StartNewLine();	//���s
	}
}

void ComponentRect::StartNewLine()
{
	startDrawY += mojiHeight + lineSpace;	//�����̑傫���ƍs�ԕ�����
}

const float ComponentRect::lineSpace = 5;