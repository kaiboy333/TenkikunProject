#include "OnOffButton.h"

OnOffButton::OnOffButton(float startX, float startY, float width, float height, Image* image, std::vector<function<void()>> buttonFunc) : WindowButton(startX, startY, width, height, image)
{
	this->buttonFunc = buttonFunc;
	this->image = image;

	//関数が2個なら
	if (buttonFunc.size() == 2) {
		//押して離したら
		onClickEvents.push_back(std::make_pair(GetEventNo(), [this]() {
			if (!isDown) {
				this->buttonFunc[0]();
			}
			else {
				this->buttonFunc[1]();
			}

			//反転させる
			isDown = !isDown;
		}));
	}
}

void OnOffButton::PreparationLibrate()
{
	//自身の解放準備
	WindowButton::PreparationLibrate();
}

void OnOffButton::Draw()
{
	//四角の描画
	unsigned int drawColor = isDown ? downColor : GetColor(255, 255, 255);
	DrawBoxAA(startX, startY, startX + width, startY + height, drawColor, TRUE);

	//マウスが乗っていてボタンが押されていなかったら
	if (GetIsTopOn() && !isDown) {
		//四角の描画
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
	}

	//画像の描画
	WindowButton::Draw();

	//枠の描画
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

}
