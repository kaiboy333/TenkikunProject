#pragma once

#include "BlodePhase.h"

class SweepAndPrune : BlodePhase
{
	public:
		SweepAndPrune(const std::vector<Collider*>& colliders);

		std::vector<std::pair<int, int>> GetHitPairCollidersIndex() override;
};

