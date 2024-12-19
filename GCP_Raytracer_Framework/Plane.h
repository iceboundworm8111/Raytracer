#pragma once
#include "BaseObject.h"

struct Plane : public BaseObject
{
public:
	Plane(glm::vec3 _position, glm::vec3 _normal, glm::vec3 _colour);//Constructor


	bool RayCollide(Ray _ray, glm::vec3& _CollidePoint);//Function for the ray collision

	glm::vec3 NormalPosition(glm::vec3 _CollidePoint);//Function for the normal position

private:
	glm::vec3 mNormal{ 0 }; //Normal of the plane
};