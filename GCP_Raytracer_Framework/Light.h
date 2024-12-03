#pragma once
#include <GLM/glm.hpp>
/// <summary>
/// This a light struct which contains the position and colour of the light
/// </summary>
struct Light
{
	glm::vec3 mPosition; /*!< Position of the light source */
	glm::vec3 mColour; /*!< Colour of the light source */

	Light(glm::vec3 _position, glm::vec3 _colour)
	{
		mPosition = _position;
		mColour = _colour;
	}
}; 