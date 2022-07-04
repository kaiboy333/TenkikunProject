#include "GameWindow.h"
#include "SceneManager.h"

GameWindow::GameWindow() : Window(300, 0, 700, 500)
{

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

    //�摜�̃A���t�@�l�ݒ�
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

    //�D�F�̎l�p��`��
    DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(169, 169, 169), TRUE);

    //�V�[���̕`��
    Scene* scene = SceneManager::GetNowScene();
    if (scene != nullptr) {
        scene->Draw(this);
    }
}
