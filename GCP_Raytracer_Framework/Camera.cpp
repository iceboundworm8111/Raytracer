#include "Camera.h"

Ray Camera::GetRay(glm::ivec2 windowPos)
{
	Ray ray;
	ray.mDirection = glm::vec3(0,0 , -1);
	ray.mOrigin = glm::vec3(windowPos.x, windowPos.y, 0);
	return ray;
}