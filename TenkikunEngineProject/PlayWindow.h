#pragma once

#include "Window.h"
#include "OnOffButton.h"

class PlayWindow : public Window
{
	public:
		PlayWindow();

		OnOffButton* playButton = nullptr;
		OnOffButton* stopButton = nullptr;

		float buttonWidth, buttonHeight;

		virtual void PreparationLibrate() override;

		virtual void Draw() override;
};

