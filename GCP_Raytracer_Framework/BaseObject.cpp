#include "BaseObject.h"



glm::vec3 BaseObject::ShadePosition(glm::vec3 _position,glm::vec3 _lightPos, glm::vec3 _lightCol, glm::vec3 _CamPos)
{
	glm::vec3 DLight = glm::normalize(_lightPos-_position);
	glm::vec3 Normal = NormalPosition(_position);

	float dotp = glm::dot(Normal, DLight);

	glm::vec3 Diffuse(0, 0, 0);

	// If the dot product is positive, calculate the diffuse light
	if (dotp > 0.0f) 
	{
		Diffuse += dotp *mColour* _lightCol;
	}
	//Specular
	glm::vec3 ViewDir = glm::normalize(_CamPos - _position);
	glm::vec3 ReflectDir = glm::normalize(glm::reflect(-DLight, Normal));
	float spec = glm::pow(glm::max(glm::dot(ViewDir, ReflectDir), 0.0f), 32);
	glm::vec3 Specular = spec * _lightCol;

	glm::vec3 Colour =  Diffuse+ Specular ;

	return Colour;
}