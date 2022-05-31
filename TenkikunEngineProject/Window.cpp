#include "Window.h"

Window::Window(int width, int height, float startX, float startY)
{
	this->width = width;
	this->height = height;
	this->startX = startX;
	this->startY = startY;
}

void Window::Draw()
{
	//�`��͈͐���
	SetDrawArea(startX, startY, startX + width- 1, startY + height - 1);
	//�����l�p��`��
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(255, 255, 255), TRUE);
	//�g����`��
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(0, 0, 0), FALSE);

}
