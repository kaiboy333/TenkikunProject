#pragma once

#include "Collider.h"
#include <vector>

class VertexCollider : public Collider
{
	public:
		VertexCollider(GameObject* gameobject);
		//�e���_���擾
		virtual std::vector<Vector2> GetVertexes() = 0;

		virtual void Draw() override;

	protected:
		std::vector<Vector2> GetVertexes(std::vector<Vector2> toVertexVecs);
};

