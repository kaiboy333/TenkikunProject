#include "GameWindow.h"
#include "SceneManager.h"

GameWindow::GameWindow() : Window(300, 0, 700, 500)
{
    frameText = new TextRect(startX, startY, "");

    //�}�E�X���������u��
    mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this]() {
        //�Q�[����ʂ��g����悤��
        WindowManager::canUseGameWnd = true;
    }));
}

void GameWindow::Update()
{
    Window::Update();

    //�V�[���̍X�V
    Scene* scene = SceneManager::GetNowScene();
    if (scene != nullptr) {
        scene->Update();
    }
}

void GameWindow::Draw()
{
    //�o�b�N�̕`��
    Window::Draw();

    //�D�F�̎l�p��`��
    DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(169, 169, 169), TRUE);

    //�V�[���̕`��
    Scene* scene = SceneManager::GetNowScene();
    if (scene != nullptr) {
        scene->Draw();
    }

    //frameText�̕`��
    frameText->Draw();
}
