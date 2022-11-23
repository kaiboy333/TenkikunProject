#include "BlodePhase.h"

BlodePhase::BlodePhase(std::vector<Collider*>& colliders)
{
	for (auto& collider : colliders) {
		rects.push_back(collider->GetBoundingBox());
	}
}