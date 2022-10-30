#include "HitInfo.h"

HitInfo::HitInfo(int colliderID1, int colliderID2, Contact contact)
{
	this->colliderID1 = colliderID1;
	this->colliderID2 = colliderID2;
	this->contact = contact;
}