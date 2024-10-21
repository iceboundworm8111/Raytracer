#include "Sphere.h"
#include <iostream>

Sphere::Sphere(glm::vec3 _position, glm::vec3 _colour, float _radius )
{
	mPosition = _position;
	mColour = _colour;
	mRadius = _radius;
}

bool Sphere::RayCollide(Ray _ray, glm::vec3& _CollidePoint)
{


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
glm::vec3 Sphere::ShadePosition(glm::vec3 _position)
{
	glm::vec3 DLight = glm::vec3(0.0f, 0.5f, 0.5f);
	glm::vec3 Normal = NormalPosition(_position);
	/*glm::vec3 DLightCol = glm::vec3(1.0f, 1.0f, 1.0f);*/
	glm::vec3 Ll = glm::dot(Normal,DLight)*mColour;
	return Ll;
}
glm::vec3 Sphere::NormalPosition(glm::vec3 _Intersectposition)
{
	return glm::normalize(_Intersectposition-mPosition);
}