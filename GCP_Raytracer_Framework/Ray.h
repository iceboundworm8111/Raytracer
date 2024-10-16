#pragma once

#include <GLM/glm.hpp>

struct Ray
{
public:

	Ray(glm::vec3& _direction, glm::vec3& _origin) { mDirection = _direction;  mOrigin = _origin; }

	glm::vec3 mOrigin;
	glm::vec3 mDirection;
private:

};