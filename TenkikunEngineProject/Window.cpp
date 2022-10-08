#include "Window.h"
#include "WindowManager.h"

//void Window::SetSelectedTriggerRect(TriggerRect* selectedTriggerRect)
//{
//	//新しいのをセット
//	this->selectedTriggerRect = selectedTriggerRect;
//}
//
//void Window::ClearSelectedTriggerRect()
//{
//	selectedTriggerRect = nullptr;
//}
//
//TriggerRect* Window::GetSelectedTriggerRect()
//{
//	return selectedTriggerRect;
//}

Window::Window(float startX, float startY, float width, float height) : Rect(startX, startY, width, height)
{

}

void Window::Update()
{

}

void Window::Draw()
{
	//描画範囲制限
	SetDrawArea((int)startX, (int)startY, (int)(startX + width), (int)(startY + height));
	//白い四角を描画
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(255, 255, 255), TRUE);
	//枠線を描画
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

}