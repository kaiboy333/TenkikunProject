#include "OnOffButton.h"

OnOffButton::OnOffButton(float startX, float startY, float width, float height, Image* image, std::vector<function<void()>> buttonFunc, unsigned int downColor) : WindowButton(startX, startY, width, height, image)
{
	this->buttonFunc = buttonFunc;
	this->downColor = downColor;

	//ŠÖ”‚ª2ŒÂ‚È‚ç
	if (buttonFunc.size() == 2) {
		//‰Ÿ‚µ‚Ä—£‚µ‚½‚ç
		onClickEvents.push_back(std::make_pair(GetEventNo(), [this]() {
			if (!isDown) {
				this->buttonFunc[0]();
			}
			else {
				this->buttonFunc[1]();
			}

			//”½“]‚³‚¹‚é
			isDown = !isDown;
		}));
	}
}

void OnOffButton::PreparationLibrate()
{
	//©g‚Ì‰ğ•ú€”õ
	WindowButton::PreparationLibrate();
}

void OnOffButton::Draw()
{
	//lŠp‚Ì•`‰æ
	unsigned int drawColor = isDown ? downColor : GetColor(255, 255, 255);
	DrawBoxAA(startX, startY, startX + width, startY + height, drawColor, TRUE);

	//‰æ‘œ‚Ì•`‰æ
	WindowButton::Draw();

	//˜g‚Ì•`‰æ
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);
}
