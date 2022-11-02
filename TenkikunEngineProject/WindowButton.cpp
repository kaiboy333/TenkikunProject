#include "WindowButton.h"
#include "DxLib.h"
#include "MyMath.h"

WindowButton::WindowButton(float startX, float startY, float width, float height, Image* image) : TriggerRect(startX, startY, width, height, 1)
{
	this->image = image;
}

void WindowButton::Draw()
{
	//�����Ȃ�`�悵�Ȃ�
	if (!isActive)
		return;

	if (image) {
		//�`��
		if (image->GetGH()) {
			DrawRotaGraph3F(startX + width / 2, startY + height / 2, image->GetWidth() / 2, image->GetHeight() / 2, width / image->GetWidth(), height / image->GetHeight(), 0, image->GetGH(), TRUE);
		}
	}
}

void WindowButton::SetImage(Image* image)
{
	this->image = image;
}

Image* WindowButton::GetImage()
{
	return image;
}

void WindowButton::PreparationLibrate()
{
	//���g�̉������
	TriggerRect::PreparationLibrate();
}
