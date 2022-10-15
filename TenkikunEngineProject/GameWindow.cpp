#include "GameWindow.h"
#include "SceneManager.h"

GameWindow::GameWindow() : Window(300, 50, 700, 450)
{
    frameText = new TextRect(startX, startY, "");
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
