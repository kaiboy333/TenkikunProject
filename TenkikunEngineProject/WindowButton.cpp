#include "WindowButton.h"
#include "DxLib.h"
#include "MyMath.h"

WindowButton::WindowButton(float startX, float startY, float width, float height) : TriggerRect(startX, startY, width, height)
{

}

void WindowButton::Draw()
{
	//無効なら描画しない
	if (!isActive)
		return;

	if (image) {
		//描画
		if (image->GetGH()) {
			DrawRotaGraph3F(startX + width / 2, startY + height / 2, image->GetWidth() / 2, image->GetHeight() / 2, width / image->GetWidth(), height / image->GetHeight(), 0, image->GetGH(), TRUE);
		}
	}
}