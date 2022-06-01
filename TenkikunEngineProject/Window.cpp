#include "Window.h"

Window::Window(float startX, float startY, float width, float height) : TriggerRect(startX, startY, width, height)
{
	
}

void Window::Draw()
{
	//�`��͈͐���
	SetDrawArea((int)startX, (int)startY, (int)(startX + width - 1), (int)(startY + height - 1));
	//�����l�p��`��
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(255, 255, 255), TRUE);
	//�g����`��
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(0, 0, 0), FALSE);

}
