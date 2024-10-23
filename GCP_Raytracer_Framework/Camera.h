#pragma once
#include "Ray.h"
#include <GLM/glm.hpp>
class Camera
{
public:
	Ray GetRay(glm::ivec2 windowPos,glm::ivec2 winSize);
	
private:
	glm::mat4 mViewMat;
	glm::mat4 mProjMat;
	glm::mat4 mModelMat;
};