#pragma once

#include <vector>
#include "Vector2.h"
#include "Collider.h"

class SupportInfo
{
	public:
		std::vector<Vector2> supports;
		int colliderID1;
		int colliderID2;

		SupportInfo(std::vector<Vector2> supports, int colliderID1, int colliderID2);
};
