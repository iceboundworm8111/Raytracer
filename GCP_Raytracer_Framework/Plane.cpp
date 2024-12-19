#include "Plane.h"

Plane::Plane(glm::vec3 _position, glm::vec3 _normal, glm::vec3 _colour)
{
	mPosition = _position;
	mNormal = _normal;
	mColour = _colour;
}

bool Plane::RayCollide(Ray _ray, glm::vec3& _CollidePoint)
{
	float denominator = glm::dot(_ray.mDirection, mNormal);//Dot product of the direction of the ray and the normal of the plane
	float rayPlaneInter = glm::dot((mPosition - _ray.mOrigin), mNormal) / denominator;//Dot product of the position of the plane and the normal of the plane divided by the dot product of the direction of the ray and the normal of the plane

	if (rayPlaneInter < 0) return false;//If the ray is behind the plane, return false

	_CollidePoint = _ray.mOrigin + (rayPlaneInter * _ray.mDirection);//Sets the collision point
	return true;
}
glm::vec3 Plane::NormalPosition(glm::vec3 _CollidePoint)
{
	return mNormal;
}