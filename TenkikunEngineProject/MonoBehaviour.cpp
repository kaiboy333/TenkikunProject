#include "MonoBehaviour.h"
#include "SceneManager.h"

MonoBehaviour::MonoBehaviour(GameObject* gameobject) : Component(gameobject)
{
}

void MonoBehaviour::Update()
{
	////ƒvƒŒƒC‚µ‚Ä‚¢‚é‚¾‚¯
	//if (SceneManager::playMode == SceneManager::PlayMode::PLAY) {
		if (isFirstUpdate) {
			MonoStart();	//Å‰‚¾‚¯ŒÄ‚Î‚ê‚é
			isFirstUpdate = false;	//2‰ñ–Ú‚©‚ç‚ÍŒÄ‚Î‚ê‚È‚¢
		}
		MonoUpdate();
	//}
}

void MonoBehaviour::PreparationLibrate()
{
	//©g‚Ì‰ğ•ú€”õ
	Component::PreparationLibrate();
}