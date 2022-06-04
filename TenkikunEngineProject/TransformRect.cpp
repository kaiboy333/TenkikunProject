#include "TransformRect.h"
#include "Transform.h"
#include "Debug.h"
#include "Transform.h"
#include "Vector3.h"
#include <sstream>

using namespace std;

TransformRect::TransformRect(float startX, float startY, Component* component) : ComponentRect(startX, startY, component, 3)
{
}

void TransformRect::Draw()
{
	ComponentRect::Draw();	//�ŏ��ɖ��O�`��

	if (component) {
		Transform* transform = static_cast<Transform*>(component);	//�L���X�g�ϊ�
		stringstream ss;

		//Position
		DrawStringF(startX, startDrawY, "Position", GetColor(0, 0, 0));	//���̕`��
		ss << "x:" << to_string(transform->position->x) << " y:" << to_string(transform->position->y).c_str() << " z:" << to_string(transform->position->z).c_str();
		DrawStringF(rightStartDrawX, startDrawY, ss.str().c_str(), GetColor(0, 0, 0));	//�E�̕`��

		StartNewLine();	//���s
		ss = stringstream();	//sstream������

		//Rotation
		DrawStringF(startX, startDrawY, "Rotation", GetColor(0, 0, 0));	//���̕`��
		ss << "x:" << to_string(transform->rotation->x) << " y:" << to_string(transform->rotation->y).c_str() << " z:" << to_string(transform->rotation->z).c_str();
		DrawStringF(rightStartDrawX, startDrawY, ss.str().c_str(), GetColor(0, 0, 0));	//�E�̕`��

		StartNewLine();	//���s
		ss = stringstream();	//sstream������

		//Scale
		DrawStringF(startX, startDrawY, "Scale", GetColor(0, 0, 0));	//���̕`��
		ss << "x:" << to_string(transform->scale->x) << " y:" << to_string(transform->scale->y).c_str() << " z:" << to_string(transform->scale->z).c_str();
		DrawStringF(rightStartDrawX, startDrawY, ss.str().c_str(), GetColor(0, 0, 0));	//�E�̕`��

	}
}
