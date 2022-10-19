
#include "SupportInfo.h"

SupportInfo::SupportInfo(std::vector<Vector2> supports, Collider* c1, Collider* c2)
{
	this->supports = supports;
	this->c1 = c1;
	this->c2 = c2;
}
