#pragma once
#include "Ray.h"
#include <GLM/glm.hpp>
class Camera
{
public:
	Camera(glm::ivec2 winsize);
	Ray GetRay(glm::ivec2 windowPos,glm::ivec2 winSize);
private:
	glm::mat4 mViewMat;
	glm::mat4 mProjMat;
	glm::mat4 mModelMat;
};