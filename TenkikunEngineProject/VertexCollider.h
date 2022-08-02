#pragma once

#include "Collider.h"
#include <vector>

class VertexCollider : public Collider
{
	public:
		VertexCollider(GameObject* gameobject);
		//各頂点を取得
		virtual std::vector<Vector3> GetVertexes() = 0;

		virtual void Draw() override;

	protected:
		std::vector<Vector3> GetVertexes(std::vector<Vector3> toVertexVecs);
};

