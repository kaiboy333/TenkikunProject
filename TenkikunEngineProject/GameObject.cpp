#include "GameObject.h"
#include "ImageRenderer.h"
#include "Animator.h"

GameObject::GameObject()
{
	Transform* transform = this->AddComponent<Transform>();	//Transform‚ð‚Â‚¢‚©
	this->transform = transform;
}

void GameObject::Update()
{
	for (Component* component : components) {
		component->Update();
	}
}

void GameObject::Draw(Window* window, Camera* camera)
{
	Component* component = nullptr;
	//ImageComponent‚ª‚ ‚é‚È‚ç
	if ((component = this->GetComponent<ImageRenderer>()) != nullptr) {
		ImageRenderer* image = static_cast<ImageRenderer*>(component);
		image->Draw(window, camera);	//•`‰æ
	}
}

void GameObject::Rename(std::string name)
{
	//TreeList‚Ì–¼‘O‚à•Ï‚¦‚é
}

GameObject* GameObject::Find(std::string name)
{
	Scene* scene = SceneManager::GetNowScene();

	for (GameObject* gameobject : scene->gameobjects) {
		if (gameobject->name == name) {
			return gameobject;
		}
	}
	return nullptr;
}
