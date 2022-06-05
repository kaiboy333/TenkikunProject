#include "TransformRect.h"
#include "Transform.h"
#include "Debug.h"
#include "Transform.h"
#include "Vector3.h"
#include <sstream>
#include <iomanip>

using namespace std;

TransformRect::TransformRect(float startX, float startY, Component* component) : ComponentRect(startX, startY, component, 3)
{
}

void TransformRect::Draw()
{
	ComponentRect::Draw();	//ç≈èâÇ…ñºëOï`âÊ

	if (component) {
		Transform* transform = static_cast<Transform*>(component);	//ÉLÉÉÉXÉgïœä∑
		stringstream ss;

		//Position
		DrawStringF(startX, startDrawY, "Position", GetColor(0, 0, 0));	//ç∂ÇÃï`âÊ
		Vector3 position = transform->position;
		ss << std::fixed << std::setprecision(2) << "x:" << position.x << " y:" << position.y << " z:" << position.z;
		DrawStringF(rightStartDrawX, startDrawY, ss.str().c_str(), GetColor(0, 0, 0));	//âEÇÃï`âÊ

		StartNewLine();	//â¸çs
		ss = stringstream();	//sstreamèâä˙âª

		//Rotation
		DrawStringF(startX, startDrawY, "Rotation", GetColor(0, 0, 0));	//ç∂ÇÃï`âÊ
		Vector3 rotation = transform->rotation;
		ss << std::fixed << std::setprecision(2) << "x:" << rotation.x << " y:" <<rotation.y << " z:" << rotation.z;
		DrawStringF(rightStartDrawX, startDrawY, ss.str().c_str(), GetColor(0, 0, 0));	//âEÇÃï`âÊ

		StartNewLine();	//â¸çs
		ss = stringstream();	//sstreamèâä˙âª

		//Scale
		DrawStringF(startX, startDrawY, "Scale", GetColor(0, 0, 0));	//ç∂ÇÃï`âÊ
		Vector3 scale = transform->scale;
		ss << std::fixed << std::setprecision(2) << "x:" << scale.x << " y:" << scale.y << " z:" << scale.z;
		DrawStringF(rightStartDrawX, startDrawY, ss.str().c_str(), GetColor(0, 0, 0));	//âEÇÃï`âÊ

	}
}
