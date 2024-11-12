#include "BaseObject.h"



glm::vec3 BaseObject::ShadePosition(glm::vec3 _position)
{
	glm::vec3 DLight = glm::vec3(0.0f, 0.8f, 0.2f);
	glm::vec3 Normal = NormalPosition(_position);
	/*glm::vec3 DLightCol = glm::vec3(1.0f, 1.0f, 1.0f);*/
	glm::vec3 Ll = glm::dot(Normal, DLight) * mColour;
	return Ll;
}