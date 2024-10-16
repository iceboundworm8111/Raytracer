#pragma once

#include <GLM/glm.hpp>
#include "Ray.h"
struct Sphere
{
public:
	Sphere(glm::vec3 mPosition, glm::vec3 mColour, float mRadius);
	~Sphere();

	bool RayCollide(Ray _ray, glm::vec3& _CollidePoint);
	glm::vec3 ShadePosition(glm::vec3 _position);
	glm::vec3 NormalPosition(glm::vec3 _Intersectposition);

private:
	glm::vec3 mPosition;
	glm::vec3 mColour;
	float mRadius;


};