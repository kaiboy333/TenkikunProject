#include "Window.h"
#include "WindowManager.h"

Window::Window(float startX, float startY, float width, float height) : TriggerRect(startX, startY, width, height, 0)
{
	//�}�E�X���������u��
	mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this]() {
		//���j���[���X�g������Ȃ�
		if (WindowManager::GetMenuList()) {
			//���j���[���X�g�̃Z�b�g������
			WindowManager::SetMenuList(nullptr);
		}
	}));
}

void Window::Update()
{

}

void Window::Draw()
{
	//�`��͈͐���
	SetDrawArea((int)startX, (int)startY, (int)(startX + width), (int)(startY + height));
	//�����l�p��`��
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(255, 255, 255), TRUE);
	//�g����`��
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);

}

void Window::PreparationLibrate()
{
	TriggerRect::PreparationLibrate();
}
