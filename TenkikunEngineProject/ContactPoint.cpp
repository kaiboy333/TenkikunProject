#include "ContactPoint.h"

ContactPoint::ContactPoint(Collider* thisCollider, Collider* otherCollider, Vector2 point, Vector2 depthPoint)
{
	this->thisCollider = thisCollider;
	this->otherCollider = otherCollider;
	this->point = point;
	this->depthPoint = depthPoint;
}
