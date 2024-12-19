#pragma once

#include <GLM/glm.hpp>

struct Ray
{
	Ray()
	{

	}
	Ray(glm::vec3 _origin, glm::vec3 _direction)//Constructor
	{
		mOrigin = _origin;
		mDirection = _direction;
	}
public:
	glm::vec3 mOrigin{ 0.0f };//Origin of the ray
	glm::vec3 mDirection{ 0.0f };//Direction of the ray

private:

};