#pragma once
#include "Ray.h"
#include <GLM/glm.hpp>
class Camera
{
public:
	Camera(glm::ivec2 winsize);//Constructor
	Ray GetRay(glm::vec2 windowPos, glm::ivec2 winSize);//Function to get the ray
private:
	glm::mat4 mViewMat;//View matrix
	glm::mat4 mProjMat;//Projection matrix
	glm::mat4 mModelMat;//Model matrix
};