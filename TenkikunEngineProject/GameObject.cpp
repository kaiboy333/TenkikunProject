#include "GameObject.h"
#include "ImageRenderer.h"
#include "Animator.h"
#include "Collider.h"

GameObject::GameObject()
{

}

void GameObject::RemoveComponent(Component* component)
{
	if ((int)components.size() != 0) {
		auto iter = std::find(components.begin(), components.end(), component);
		//���������Ȃ�
		if (iter != components.end()) {
			//�R���|�[�l���g�̃��X�g����폜
			components.erase(std::remove(components.begin(), components.end(), component));
			//���
			delete(component);
			component = nullptr;
		}
	}
}

void GameObject::Update()
{
	for (Component* component : components) {
		component->Update();
	}
}

void GameObject::Draw()
{
	for (Component* component : components) {
		auto& type = typeid(*component);
		//DrawComponent������Ȃ�
		if (dynamic_cast<DrawComponent*>(component) != nullptr) {
			DrawComponent* drawComponent = static_cast<DrawComponent*>(component);
			drawComponent->Draw();	//�`��
		}
	}
}

void GameObject::SetTreeNodeName(std::string name)
{
	//TreeList�̖��O��ς���
	TreeList* treeList = SceneManager::GetNowScene()->treeList;
	TreeNode* node = treeList->FindNode(this->name);	//���̖��O�ŒT��
	if (node) {
		//���O�Z�b�g
		node->SetElement(name);
	}
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

void GameObject::SetName(std::string name)
{
	std::string newName = name;
	int no = 1;	//���h�~�p�ԍ�
	//���Ȃ��Ȃ�܂ŌJ��Ԃ�
	while (GameObject::Find(newName)) {
		newName = name + " (" + std::to_string(no++) + ")";	//�V�������̖��O���쐬
	}
	SetTreeNodeName(newName);	//TreeNode�̖��O��ς���
	this->name = newName;	//���ۂɕς���
}

std::string GameObject::GetName()
{
	return name;
}
