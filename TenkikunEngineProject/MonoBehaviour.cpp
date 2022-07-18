#include "MonoBehaviour.h"
#include "SceneManager.h"

void MonoBehaviour::Update()
{
	//ƒvƒŒƒC‚µ‚Ä‚¢‚é‚¾‚¯
	if (SceneManager::playMode == SceneManager::PlayMode::PLAY) {
		if (isFirstUpdate) {
			MonoStart();	//Å‰‚¾‚¯ŒÄ‚Î‚ê‚é
			isFirstUpdate = false;	//2‰ñ–Ú‚©‚ç‚ÍŒÄ‚Î‚ê‚È‚¢
		}
		MonoUpdate();
	}
}
