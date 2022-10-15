#include "Component.h"
#include "ProjectFileManager.h"

Component::Component(GameObject* gameobject)
{
	this->gameobject = gameobject;
}

void Component::PreparationLibrate()
{
	gameobject = nullptr;

	//sceneInfos����폜
	ProjectFileManager::sceneInfos.erase(this->fileID);
}
