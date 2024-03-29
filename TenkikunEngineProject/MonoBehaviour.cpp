#include "MonoBehaviour.h"
#include "SceneManager.h"

MonoBehaviour::MonoBehaviour(GameObject* gameobject) : Component(gameobject)
{
}

void MonoBehaviour::Update()
{
	////プレイしている時だけ
	//if (SceneManager::playMode == SceneManager::PlayMode::PLAY) {
		if (isFirstUpdate) {
			MonoStart();	//最初だけ呼ばれる
			isFirstUpdate = false;	//2回目からは呼ばれない
		}
		MonoUpdate();
	//}
}

void MonoBehaviour::PreparationLibrate()
{
	//自身の解放準備
	Component::PreparationLibrate();
}