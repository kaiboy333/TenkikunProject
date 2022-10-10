#include "Window.h"
#include "WindowManager.h"

Window::Window(float startX, float startY, float width, float height) : TriggerRect(startX, startY, width, height, 0)
{
	//マウスを押した瞬間
	mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		//メニューリストがあるなら
		if (WindowManager::GetMenuList()) {
			//メニューリストのセットを解除
			WindowManager::SetMenuList(nullptr);
		}
	}));
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

void Window::PreparationLibrate()
{
	TriggerRect::PreparationLibrate();
}
