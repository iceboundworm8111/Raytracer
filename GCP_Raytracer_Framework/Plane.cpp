#include "Plane.h"

Plane::Plane(glm::vec3 _position, glm::vec3 _normal, glm::vec3 _colour)
{
	mPosition = _position;
	mNormal = _normal;
	mColour = _colour;
}

bool Plane::RayCollide(Ray _ray, glm::vec3& _CollidePoint)
{
	float denominator = glm::dot(_ray.mDirection, mNormal);
	float rayPlaneInter = glm::dot((mPosition - _ray.mOrigin), mNormal) / denominator;

	if (rayPlaneInter < 0) return false;

	_CollidePoint = _ray.mOrigin + (rayPlaneInter * _ray.mDirection);
	return true;
}
glm::vec3 Plane::NormalPosition(glm::vec3 _CollidePoint)
{
	return mNormal;
}