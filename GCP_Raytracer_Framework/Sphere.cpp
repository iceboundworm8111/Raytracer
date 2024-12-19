#include "Sphere.h"
#include <iostream>

Sphere::Sphere(glm::vec3 _position, glm::vec3 _colour, float _radius )
{
	mPosition = _position;
	mColour = _colour;
	mRadius = _radius;
}

bool Sphere::RayCollide(Ray _ray, glm::vec3& _CollidePoint)//Function for the ray collision
{
	glm::vec3 L = mPosition - _ray.mOrigin;//Position of the sphere minus the origin of the ray
	float tc = glm::dot(L, _ray.mDirection);//Dot product of the position of the sphere and the direction of the ray


	if (tc < 0.0)//If the dot product is less than 0
	{
		 return false;
	}

	float d2 = glm::dot(L, L) - (tc * tc);//Dot product of the position of the sphere and the direction of the ray


	float radius2 = mRadius * mRadius;//Radius of the sphere squared

	if (d2 > radius2)//If the dot product is greater than the radius squared
	{
		return false;
	}

	float t1c = glm::sqrt(radius2 - d2);//Square root of the radius squared minus the dot product	

	float t1 = tc - t1c;

	_CollidePoint = _ray.mOrigin + (_ray.mDirection * t1);//Sets the collision point

	return true;
}

glm::vec3 Sphere::NormalPosition(glm::vec3 _CollidePoint)
{
	return glm::normalize(_CollidePoint -mPosition);
}