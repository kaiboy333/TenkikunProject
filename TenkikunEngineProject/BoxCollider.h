#pragma once

#include "VertexCollider.h"

class BoxCollider : public VertexCollider
{
	public:
		Vector3 size = Vector3(5, 5, 0);

		BoxCollider(GameObject* gameobject);

		virtual std::vector<Vector2> GetVertexes() const override;

		float GetActualWidth() const;
		float GetActualHeight() const;

		virtual float GetI() const override;	//Šµ«ƒ‚[ƒƒ“ƒg‚ğæ“¾
};

