#include "Sphere.h"

Sphere::Sphere(glm::vec3 _position, glm::vec3 _colour, float _radius )
{
	mPosition = _position;
	mColour = _colour;
	mRadius = _radius;
}

bool Sphere::RayCollide(Ray _ray, glm::vec3& _CollidePoint)
{
	bool doesRayCollide = true;

	glm::vec3 L = mPosition - _ray.mOrigin;
	float tc = glm::dot(L, _ray.mOrigin);


	if (tc < 0.0 == false)
	{
		doesRayCollide = false;
	}

	float d2 = glm::dot(L, L) - (tc * tc);

	if (d2 > mRadius)
	{
		doesRayCollide = false;
	}

	float radius2 = mRadius * mRadius;

	float t1c = glm::sqrt(radius2 - d2);

	float t1 = tc - t1c;

	_CollidePoint = _ray.mOrigin + (_ray.mDirection + t1);

	return doesRayCollide;
}
glm::vec3 Sphere::ShadePosition(glm::vec3 _position)
{
	return mColour;
}
glm::vec3 Sphere::NormalPosition(glm::vec3 _Intersectposition)
{
	return glm::normalize(mPosition - _Intersectposition);
}