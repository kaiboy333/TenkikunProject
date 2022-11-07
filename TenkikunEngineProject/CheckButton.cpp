#include "CheckButton.h"

CheckButton::CheckButton(float startX, float startY, float width, float height, std::vector<Image*> images) : OnOffButton(startX, startY, width, height, images[0], { [this, images] {this->isChecked = true; this->image = images[1]; }, [this, images] {this->isChecked = false; this->image = images[0]; } })
{

}

bool CheckButton::GetIsChecked()
{
	return isChecked;
}

void CheckButton::SetIsChecked(bool isChecked)
{
	if (isChecked) {
		this->buttonFunc[0]();
	}
	else {
		this->buttonFunc[1]();
	}
}
