#pragma once

#include "TriggerRect.h"
#include "TextButton.h"

class SelectRect : public TriggerRect
{
	public:
		std::vector<TextButton*> choices;	//�I��������

		SelectRect(float startX, float startY, float width, float height, std::vector<std::string> strs);

		void Draw() override;

		virtual void PreparationLibrate() override;

		void SetStrs(std::vector<std::string> strs);

		int GetNo();

	private:
		int nowNo = 0;	//���ݑI��ł���No
};
