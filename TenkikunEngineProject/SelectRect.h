#pragma once

#include "TriggerRect.h"
#include "TextButton.h"

class SelectRect : public TriggerRect
{
	public:
		std::vector<TextButton*> choices;	//‘I‘ğˆ‚½‚¿

		SelectRect(float startX, float startY, float width, float height, std::vector<std::string> strs, int nowNo = 0);

		void Draw() override;

		virtual void PreparationLibrate() override;

		void SetStrs(std::vector<std::string> strs);

		int GetNowNo();
		void SetNowNo(int nowNo);

	private:
		int nowNo = 0;	//Œ»İ‘I‚ñ‚Å‚¢‚éNo
};

