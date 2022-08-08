#include "Time.h"
#include "WindowManager.h"

Time::Time()
{
	
	if (QueryPerformanceFrequency(&timeFreq) == FALSE) {

	}

	//開始時刻を記録
	QueryPerformanceCounter(&beforeTime);
}

void Time::Update()
{
	// 今の時間を取得
	QueryPerformanceCounter(&nowTime);
	// (今の時間 - 前フレームの時間) / 周波数 = 経過時間(秒単位)
	double frameTime = static_cast<double>(nowTime.QuadPart - beforeTime.QuadPart) / static_cast<double>(timeFreq.QuadPart);

	if (frameTime < MIN_FRAME_TIME) { // 時間に余裕がある
		// ミリ秒に変換
		DWORD sleepTime = static_cast<DWORD>((MIN_FRAME_TIME - frameTime) * 1000);

		timeBeginPeriod(1); // 分解能を上げる(こうしないとSleepの精度はガタガタ)
		Sleep(sleepTime);   // 寝る
		timeEndPeriod(1);   // 戻す
	}
	else {
		//Debug::Log("処理落ち");
	}

	QueryPerformanceCounter(&nowTime);
	//前回からの経過時間を求める
	double elapsedTime = static_cast<double>(nowTime.QuadPart - beforeTime.QuadPart) / static_cast<double>(timeFreq.QuadPart);
	double fps = 1 / elapsedTime;

	deltaTime = static_cast<float>(elapsedTime);
	time += deltaTime;

	//前回のUpdateからどのくらい経ったか計算する

	beforeTime = nowTime;

	sumFPS += fps;
	frameCount++;
	if (frameCount % FPS == 0) {
		fps = sumFPS / FPS;
		sumFPS = 0;
		frameCount = 0;
		WindowManager::gameWindow->frameText->SetText("FPS : " + std::to_string(fps));	//FPSを表示
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

