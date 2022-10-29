#include "HitInfo.h"

HitInfo::HitInfo(Collider* c1, Collider* c2, Vector3 n, float sink, Vector3 contactPoint)
{
	this->c1 = c1;
	this->c2 = c2;
	this->n = n;
	this->sink = sink;
	this->contactPoint = contactPoint;
}
