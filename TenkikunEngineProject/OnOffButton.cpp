#include "OnOffButton.h"

OnOffButton::OnOffButton(float startX, float startY, float width, float height, Image* image, std::vector<function<void()>> buttonFunc) : WindowButton(startX, startY, width, height, image)
{
	this->buttonFunc = buttonFunc;
	this->image = image;

	//�֐���2�Ȃ�
	if (buttonFunc.size() == 2) {
		//�����ė�������
		onClickEvents.push_back(std::make_pair(GetEventNo(), [this]() {
			if (!isDown) {
				this->buttonFunc[0]();
			}
			else {
				this->buttonFunc[1]();
			}

			//���]������
			isDown = !isDown;
		}));
	}
}

void OnOffButton::PreparationLibrate()
{
	//���g�̉������
	WindowButton::PreparationLibrate();
}

void OnOffButton::Draw()
{
	//�l�p�̕`��
	unsigned int drawColor = isDown ? downColor : GetColor(255, 255, 255);
	DrawBoxAA(startX, startY, startX + width, startY + height, drawColor, TRUE);

	//�}�E�X������Ă��ă{�^����������Ă��Ȃ�������
	if (GetIsTopOn() && !isDown) {
		//�l�p�̕`��
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
	}

	//�摜�̕`��
	WindowButton::Draw();

	//�g�̕`��
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

}
