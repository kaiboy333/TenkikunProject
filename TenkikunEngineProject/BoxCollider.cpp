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

std::vector<Vector2> BoxCollider::GetVertexes()
{
	//中心位置から各頂点までのベクトルを作る
	std::vector<Vector2> toVertexVecs;
	//スケール取得
	Vector3 scale = gameobject->transform->scale;

	//左上の頂点へのベクトル
	toVertexVecs.push_back(Vector2(-size.x / 2 * scale.x, size.y / 2 * scale.y));
	//右上の頂点へのベクトル
	toVertexVecs.push_back(Vector2(size.x / 2 * scale.x, size.y / 2 * scale.y));
	//右下の頂点へのベクトル
	toVertexVecs.push_back(Vector2(size.x / 2 * scale.x, -size.y / 2 * scale.y));
	//左下の頂点へのベクトル
	toVertexVecs.push_back(Vector2(-size.x / 2 * scale.x, -size.y / 2 * scale.y));

	//頂点を取得、それを返す
	return VertexCollider::GetVertexes(toVertexVecs);
}