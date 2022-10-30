
#include "SupportInfo.h"

SupportInfo::SupportInfo(std::vector<Vector2> supports, int colliderID1, int colliderID2)
{
	this->supports = supports;
	this->colliderID1 = colliderID1;
	this->colliderID2 = colliderID2;
}
