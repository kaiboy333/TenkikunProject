#include "Time.h"
#include "WindowManager.h"

Time::Time()
{
	
	if (QueryPerformanceFrequency(&timeFreq) == FALSE) {

	}

	//�J�n�������L�^
	QueryPerformanceCounter(&beforeTime);
}

void Time::Update()
{
	// ���̎��Ԃ��擾
	QueryPerformanceCounter(&nowTime);
	// (���̎��� - �O�t���[���̎���) / ���g�� = �o�ߎ���(�b�P��)
	double frameTime = static_cast<double>(nowTime.QuadPart - beforeTime.QuadPart) / static_cast<double>(timeFreq.QuadPart);

	if (frameTime < MIN_FRAME_TIME) { // ���Ԃɗ]�T������
		// �~���b�ɕϊ�
		DWORD sleepTime = static_cast<DWORD>((MIN_FRAME_TIME - frameTime) * 1000);

		timeBeginPeriod(1); // ����\���グ��(�������Ȃ���Sleep�̐��x�̓K�^�K�^)
		Sleep(sleepTime);   // �Q��
		timeEndPeriod(1);   // �߂�
	}
	else {
		//Debug::Log("��������");
	}

	QueryPerformanceCounter(&nowTime);
	//�O�񂩂�̌o�ߎ��Ԃ����߂�
	double elapsedTime = static_cast<double>(nowTime.QuadPart - beforeTime.QuadPart) / static_cast<double>(timeFreq.QuadPart);
	double fps = 1 / elapsedTime;

	deltaTime = static_cast<float>(elapsedTime);
	time += deltaTime;

	//�O���Update����ǂ̂��炢�o�������v�Z����

	beforeTime = nowTime;

	sumFPS += fps;
	frameCount++;
	if (frameCount % FPS == 0) {
		fps = sumFPS / FPS;
		sumFPS = 0;
		frameCount = 0;
		WindowManager::gameWindow->frameText->SetText("FPS : " + std::to_string(fps));	//FPS��\��
	}
}

float Time::GetTime() {
	return time;
}

float Time::GetDeltaTime() {
	return deltaTime;
}

float Time::time = 0;
float Time::deltaTime = 0;

const int Time::FPS = 60;
const float Time::MIN_FRAME_TIME = 1.0f / FPS;
LARGE_INTEGER Time::beforeTime;
LARGE_INTEGER Time::nowTime;
LARGE_INTEGER Time::timeFreq;

int Time::frameCount = 0;
double Time::sumFPS = 0;

