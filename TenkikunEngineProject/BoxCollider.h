#pragma once

#include "VertexCollider.h"

class BoxCollider : public VertexCollider
{
	public:
		Vector3 size = Vector3(5, 5, 0);

		BoxCollider(GameObject* gameobject);

		virtual std::vector<Vector2> GetVertexes() override;

		float GetActualWidth();
		float GetActualHeight();

		virtual float GetI();	//Šµ«ƒ‚[ƒƒ“ƒg‚ğæ“¾
};

