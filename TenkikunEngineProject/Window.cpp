#include "Window.h"
#include "WindowManager.h"

Window::Window(float startX, float startY, float width, float height) : TriggerRect(startX, startY, width, height)
{

}

void Window::Update()
{

}

void Window::Draw()
{
	//•`‰æ”ÍˆÍ§ŒÀ
	SetDrawArea((int)startX, (int)startY, (int)(startX + width), (int)(startY + height));
	//”’‚¢lŠp‚ğ•`‰æ
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(255, 255, 255), TRUE);
	//˜gü‚ğ•`‰æ
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

}