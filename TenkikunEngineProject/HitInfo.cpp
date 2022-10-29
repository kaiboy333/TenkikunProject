#include "HitInfo.h"

HitInfo::HitInfo(Collider* c1, Collider* c2, Contact contact)
{
	this->c1 = c1;
	this->c2 = c2;
	this->contact = contact;
}
