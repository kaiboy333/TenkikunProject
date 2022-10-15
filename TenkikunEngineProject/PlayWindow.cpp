#include "PlayWindow.h"
#include "ProjectFileManager.h"

PlayWindow::PlayWindow() : Window(300, 0, 700, 50)
{
	buttonWidth = 25;
	buttonHeight = height / 2;
	float centerX = startX + width / 2;
	float centerY = startY + height / 2;

	std::vector<std::function<void()>> stopButtonFunc = {
		[]() {
			if (SceneManager::playMode == SceneManager::PlayMode::PLAY) {
				SceneManager::playMode = SceneManager::PlayMode::STOP;
			}
		},
		[this]() {
			if (playButton->isDown) {
				SceneManager::playMode = SceneManager::PlayMode::PLAY;
			}
		},
	};
	stopButton = new OnOffButton(centerX, centerY - buttonHeight / 2, buttonWidth, buttonHeight, static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\Stop.png"]), stopButtonFunc);

	std::vector<std::function<void()>> playButtonFunc = {
		[this]() {
			if (stopButton->isDown) {
				SceneManager::playMode = SceneManager::PlayMode::STOP;
			}
			else {
				SceneManager::playMode = SceneManager::PlayMode::PLAY;
			}
			SceneManager::LoadScene(SceneManager::GetNowScene()->GetName());
		},
		[]() {
			SceneManager::playMode = SceneManager::PlayMode::EDIT;
			SceneManager::LoadScene(SceneManager::GetNowScene()->GetName());
		},
	};
	playButton = new OnOffButton(centerX - buttonWidth, centerY - buttonHeight / 2, buttonWidth, buttonHeight, static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\RightArrow.png"]), playButtonFunc);
}

void PlayWindow::PreparationLibrate()
{
	//playButton�̉������
	playButton->PreparationLibrate();
	//���
	delete(playButton);
	playButton = nullptr;

	//stopButton�̉������
	stopButton->PreparationLibrate();
	//���
	delete(stopButton);
	stopButton = nullptr;

	//���g�̉������
	Window::PreparationLibrate();
}

void PlayWindow::Draw()
{
	Window::Draw();

	//playButton�̕`��
	playButton->Draw();
	//stopButton�̕`��
	stopButton->Draw();
}
