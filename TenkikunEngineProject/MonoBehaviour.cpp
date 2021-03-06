#include "MonoBehaviour.h"
#include "SceneManager.h"

void MonoBehaviour::Update()
{
	//プレイしている時だけ
	if (SceneManager::playMode == SceneManager::PlayMode::PLAY) {
		if (isFirstUpdate) {
			MonoStart();	//最初だけ呼ばれる
			isFirstUpdate = false;	//2回目からは呼ばれない
		}
		MonoUpdate();
	}
}
