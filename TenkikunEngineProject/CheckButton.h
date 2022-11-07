#pragma once

#include "OnOffButton.h"

class CheckButton : public OnOffButton
{
	public:
		CheckButton(float startX, float startY, float width, float height, std::vector<Image*> images);

		bool GetIsChecked();
		void SetIsChecked(bool isChecked);

	private:
		//チェックがついているか
		bool isChecked = false;
};

