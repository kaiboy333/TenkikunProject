#include "BoxCollider.h"
#include "ImageRenderer.h"
#include "RigidBody.h"

BoxCollider::BoxCollider(GameObject* gameobject) : VertexCollider(gameobject)
{
	//ImageRenderer取得
	ImageRenderer* ir = this->gameobject->GetComponent<ImageRenderer>();

	if (ir) {
		//Imageがあるなら
		if (ir->image) {
			//幅、高さをsizeにセット
			size.x = ir->image->GetWidth();
			size.y = ir->image->GetHeight();
		}
	}
}

std::vector<Vector2> BoxCollider::GetVertexes()
{
	//中心位置から各頂点までのベクトルを作る
	std::vector<Vector2> toVertexVecs;

	//左上の頂点へのベクトル
	toVertexVecs.push_back(Vector2(-GetActualWidth() / 2, GetActualHeight() / 2));
	//右上の頂点へのベクトル
	toVertexVecs.push_back(Vector2(GetActualWidth() / 2, GetActualHeight() / 2));
	//右下の頂点へのベクトル
	toVertexVecs.push_back(Vector2(GetActualWidth() / 2, -GetActualHeight() / 2));
	//左下の頂点へのベクトル
	toVertexVecs.push_back(Vector2(-GetActualWidth() / 2, -GetActualHeight() / 2));

	//頂点を取得、それを返す
	return VertexCollider::GetVertexes(toVertexVecs);
}

float BoxCollider::GetActualWidth()
{
	//スケール取得
	Vector3 scale = gameobject->transform->scale;

	return size.x * scale.x;
}

float BoxCollider::GetActualHeight()
{
	//スケール取得
	Vector3 scale = gameobject->transform->scale;

	return size.y * scale.y;
}

float BoxCollider::GetI()
{
	auto rb = gameobject->GetComponent<RigidBody>();

	return rb ? 1.0f / 3 * rb->mass * (std::powf(GetActualWidth() / 2, 2) + std::powf(GetActualHeight() / 2, 2)) : FLT_MAX;
}
