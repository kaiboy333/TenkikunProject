#include "WindowButton.h"
#include "DxLib.h"
#include "MyMath.h"

WindowButton::WindowButton(float startX, float startY, float width, float height) : TriggerRect(startX, startY, width, height)
{

}

void WindowButton::Draw()
{
	//–³Œø‚È‚ç•`‰æ‚µ‚È‚¢
	if (!isActive)
		return;

	if (image) {
		//•`‰æ
		if (image->GetGH()) {
			DrawRotaGraph3F(startX + width / 2, startY + height / 2, image->GetWidth() / 2, image->GetHeight() / 2, width / image->GetWidth(), height / image->GetHeight(), 0, image->GetGH(), TRUE);
		}
	}
}

void WindowButton::PreparationLibrate()
{
	//©g‚Ì‰ğ•ú€”õ
	TriggerRect::PreparationLibrate();
}
