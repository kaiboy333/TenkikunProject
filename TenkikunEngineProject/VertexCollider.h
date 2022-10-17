#pragma once

#include "Collider.h"
#include <vector>

class VertexCollider : public Collider
{
	public:
		VertexCollider(GameObject* gameobject);
		//各頂点を取得
		virtual std::vector<Vector2> GetVertexes() = 0;

		virtual void Draw() override;

		virtual Rect GetBoundingBox() override;	//バウンディングボックスを返す

	protected:
		std::vector<Vector2> GetVertexes(std::vector<Vector2> toVertexVecs);
};

