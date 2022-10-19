#pragma once

#include <vector>
#include "Vector2.h"
#include "Collider.h"

class SupportInfo
{
	public:
		std::vector<Vector2> supports;
		Collider* c1 = nullptr;
		Collider* c2 = nullptr;

		SupportInfo(std::vector<Vector2> supports, Collider* c1, Collider* c2);
};
