#include "BoxCollider.h"
#include "ImageRenderer.h"

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

std::vector<Vector3> BoxCollider::GetVertexes()
{
	//中心位置から各頂点までのベクトルを作る
	std::vector<Vector3> toVertexVecs;
	//スケール取得
	Vector3 scale = gameobject->transform->scale;

	//左上の頂点へのベクトル
	toVertexVecs.push_back(Vector3(-size.x / 2 * scale.x, -size.y / 2 * scale.y, 0));
	//右上の頂点へのベクトル
	toVertexVecs.push_back(Vector3(size.x / 2 * scale.x, -size.y / 2 * scale.y, 0));
	//右下の頂点へのベクトル
	toVertexVecs.push_back(Vector3(size.x / 2 * scale.x, size.y / 2 * scale.y, 0));
	//左下の頂点へのベクトル
	toVertexVecs.push_back(Vector3(-size.x / 2 * scale.x, size.y / 2 * scale.y, 0));

	//頂点を取得、それを返す
	return VertexCollider::GetVertexes(toVertexVecs);
}