#include "Sphere.h"
#include "Timer.h"
#include <iostream>

Sphere::Sphere(glm::vec3 _position, glm::vec3 _colour, float _radius )
{
	mPosition = _position;
	mColour = _colour;
	mRadius = _radius;
}

bool Sphere::RayCollide(Ray _ray, glm::vec3& _CollidePoint)
{

	//ScopedTimer Timer("RayCollide");
	glm::vec3 L = mPosition - _ray.mOrigin;
	float tc = glm::dot(L, _ray.mDirection);


	if (tc < 0.0)
	{
		 return false;
	}

	float d2 = glm::dot(L, L) - (tc * tc);



	float radius2 = mRadius * mRadius;

	if (d2 > radius2)
	{
		return false;
	}

	float t1c = glm::sqrt(radius2 - d2);

	float t1 = tc - t1c;

	_CollidePoint = _ray.mOrigin + (_ray.mDirection * t1);

	return true;
}

glm::vec3 Sphere::NormalPosition(glm::vec3 _CollidePoint)
{
	return glm::normalize(_CollidePoint -mPosition);
}