#pragma once
#include "TriggerRect.h"
class TextButton : public TriggerRect
{
public:
	TextButton(float startX, float startY, float width, float height, int eventNo, std::string text = "");

	void Draw();

	void SetText(std::string text);
	std::string GetText();

	virtual void PreparationLibrate() override;

private:
	std::string text;	//•¶Žš
};

