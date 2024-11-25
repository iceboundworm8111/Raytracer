#include "BaseObject.h"



glm::vec3 BaseObject::ShadePosition(glm::vec3 _position,glm::vec3 _lightPos)
{
	glm::vec3 DLight = glm::normalize(_lightPos-_position);
	glm::vec3 Normal = NormalPosition(_position);

	glm::vec3 Colour = glm::max(glm::dot(Normal, DLight),0.0f) * mColour;
	return Colour;
}