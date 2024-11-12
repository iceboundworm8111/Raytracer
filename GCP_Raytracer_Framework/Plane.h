#pragma once
#include "BaseObject.h"

struct Plane : public BaseObject
{
public:
	Plane(glm::vec3 _position,glm::vec3 _normal, glm::vec3 _colour);


	bool RayCollide(Ray _ray, glm::vec3& _CollidePoint);

	glm::vec3 NormalPosition(glm::vec3 _CollidePoint);

private:
	glm::vec3 mNormal{ 0 };
};