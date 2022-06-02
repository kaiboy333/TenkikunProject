#pragma once

#include "TriggerRect.h"
#include <functional>
#include "Image.h"

using namespace std;

class WindowButton : public TriggerRect
{
	public:
		//�{�^���������ꂽ���ɌĂԊ֐�����
		vector<function<void()>> onClickEvents;

		Image* image = nullptr;	//�摜

		WindowButton(float startX, float startY, float width, float height);

		void Draw();

	private:
		//�{�^������������
		bool isClicking = false;

		void OnClickEvent();	//�{�^���������ꂽ���ɌĂԃC�x���g

};

