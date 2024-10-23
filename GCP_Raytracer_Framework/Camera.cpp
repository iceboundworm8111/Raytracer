#include "Camera.h"
#include<iostream>

Ray Camera::GetRay(glm::ivec2 windowPos,glm::ivec2 winSize)
{
	Ray ray;
	glm::vec2 newWinPos;
	newWinPos.x = (float(windowPos.x) / float(winSize.x) * 2) - 1;
	newWinPos.y = (float (windowPos.y) /float( winSize.y) *2.0f) -1.0f;

	ray.mDirection = glm::vec3(0,0 , -1);
	ray.mOrigin = glm::vec3(windowPos.x, windowPos.y, 0);
	return ray;
}