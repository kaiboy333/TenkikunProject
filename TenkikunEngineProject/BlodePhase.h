#pragma once

#include <vector>
#include "Collider.h"

class BlodePhase
{
	public:
		BlodePhase(std::vector<Collider*>& colliders);

		virtual std::vector<std::pair<int, int>> GetHitPairCollidersIndex() = 0;

	protected:
		std::vector<Rect> rects;
};

