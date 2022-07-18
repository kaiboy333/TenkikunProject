#include "Script.h"
#include "SceneManager.h"

//void Script::SetMonoBehaviour(MonoBehaviour* mono)
//{
//	this->mono = mono;
//	//MonoBehaviourにゲームオブジェクトとTransformをセット
//	this->mono->gameobject = gameobject;
//	this->mono->transform = gameobject->transform;
//}
//
//MonoBehaviour* Script::GetMonoBehaviour()
//{
//	return mono;
//}
//
//void Script::Update()
//{
//	if (mono) {
//		//プレイしている時だけ
//		if (SceneManager::playMode == SceneManager::PlayMode::PLAY) {
//			if (isFirstUpdate) {
//				mono->Start();	//最初だけ呼ばれる
//				isFirstUpdate = false;	//2回目からは呼ばれない
//			}
//			mono->Update();
//		}
//	}
//}
