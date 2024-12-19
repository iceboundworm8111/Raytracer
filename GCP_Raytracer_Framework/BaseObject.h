#pragma once

#include <GLM/glm.hpp>
#include "Ray.h"

struct BaseObject
{
public:
	BaseObject() {}

	
	virtual bool RayCollide(Ray _ray, glm::vec3& _CollidePoint) = 0; //Pure virtual function for the ray collision
	virtual glm::vec3 NormalPosition(glm::vec3 _CollidePoint) = 0;//Pure virtual function for the normal position

	glm::vec3 ShadePosition(glm::vec3 _position, glm::vec3 _lightPos, glm::vec3 _lightCol, glm::vec3 _CamPos);//Function for shading the position
	
	glm::vec3 mPosition = glm::vec3(0.0f, 0.0f, 0.0f);//Position of the object
	glm::vec3 mColour = glm::vec3(0.0f, 0.0f, 0.0f);//Colour of the object
	float mReflectivity = 0.0f;//Reflectivity of the object
private:

};