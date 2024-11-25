#pragma once
#include <GLM/glm.hpp>

struct Light
{
	glm::vec3 mPosition;
	glm::vec3 mColour;

	Light(glm::vec3 _position, glm::vec3 _colour)
	{
		mPosition = _position;
		mColour = _colour;
	}
};