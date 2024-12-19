#pragma once
#include "BaseObject.h"
#include "Ray.h"
#include <GLM/glm.hpp>

struct Sphere : public BaseObject
{
public:
	Sphere(glm::vec3 mPosition, glm::vec3 mColour, float mRadius);//Constructor


	bool RayCollide(Ray _ray, glm::vec3& _CollidePoint);//Function for the ray collision
	glm::vec3 NormalPosition(glm::vec3 _CollidePoint);//Function for the normal position

private:
	float mRadius;//Radius of the sphere


};