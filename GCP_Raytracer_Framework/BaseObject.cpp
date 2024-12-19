#include "BaseObject.h"



glm::vec3 BaseObject::ShadePosition(glm::vec3 _position,glm::vec3 _lightPos, glm::vec3 _lightCol, glm::vec3 _CamPos)
{
	glm::vec3 DLight = glm::normalize(_lightPos - _position);//Direction of the light
	glm::vec3 Normal = NormalPosition(_position);//Normal of the object

	float dotp = glm::dot(Normal, DLight);//Dot product of the normal and the direction of the light

	glm::vec3 Diffuse(0, 0, 0);

	// If the dot product is positive, calculate the diffuse light
	if (dotp > 0.0f) 
	{
		Diffuse += dotp *mColour* _lightCol;
	}
	//Specular
	glm::vec3 ViewDir = glm::normalize(_CamPos - _position);//View direction
	glm::vec3 ReflectDir = glm::normalize(glm::reflect(-DLight, Normal));//Reflect direction
	float spec = glm::pow(glm::max(glm::dot(ViewDir, ReflectDir), 0.0f), 32);//Specular power
	glm::vec3 Specular = spec * _lightCol;//Specular light

	glm::vec3 Colour = Diffuse + Specular;//Colour of the object

	return Colour;
}