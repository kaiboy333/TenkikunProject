#include "Window.h"

Window::Window(float startX, float startY, float width, float height) : TriggerRect(startX, startY, width, height)
{
	
}

void Window::Draw()
{
	//•`‰æ”ÍˆÍ§ŒÀ
	SetDrawArea((int)startX, (int)startY, (int)(startX + width - 1), (int)(startY + height - 1));
	//”’‚¢lŠp‚ğ•`‰æ
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(255, 255, 255), TRUE);
	//˜gü‚ğ•`‰æ
	DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(0, 0, 0), FALSE);

}
