#include "WindowButton.h"
#include "DxLib.h"
#include "MyMath.h"

WindowButton::WindowButton(float startX, float startY, float width, float height) : TriggerRect(startX, startY, width, height)
{
	this->mouseClickDownEvents.push_back([this]() {
		//マウスが乗っていたら
		if (isOn) {
			isClicking = true;
		}
	});

	this->mouseClickUpEvents.push_back([this]() {
		//前にクリックしていたなら
		if (isClicking) {
			OnClickEvent();
		}
	});

	this->mouseExitEvents.push_back([this]() {
		isClicking = false;
	});
}

void WindowButton::Draw()
{
	//無効なら描画しない
	if (!isActive)
		return;

	if (image) {
		//描画
		DrawBoxAA(startX, startY, startX + width - 1, startY + height - 1, GetColor(0, 0, 0), TRUE);

		if (image->GetGH()) {
			DrawRotaGraph3F(startX + width / 2, startY + height / 2, image->GetWidth() / 2, image->GetHeight() / 2, width / image->GetWidth(), height / image->GetHeight(), 0, *image->GetGH(), TRUE);
		}
	}
}

void WindowButton::OnClickEvent()
{
	for (function<void()> func : onClickEvents) {
		func();
	}
}
