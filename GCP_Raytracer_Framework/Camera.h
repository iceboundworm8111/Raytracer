#pragma once
#include "Ray.h"
#include <GLM/glm.hpp>
class Camera
{
public:
	Ray GetRay(glm::ivec2 windowPos);
	
private:
	glm::mat4 mView;
	glm::mat4 mProj;
};