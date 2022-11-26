#include "BlodePhase.h"
#include "Debug.h"

BlodePhase::BlodePhase(const std::vector<Collider*>& colliders)
{
	for (auto& collider : colliders) {
		rects.push_back(collider->GetBoundingBox());
	}
}