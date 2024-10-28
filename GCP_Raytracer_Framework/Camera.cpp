#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include<iostream>

Camera::Camera(glm::ivec2 winSize)
{
	mProjMat = glm::perspective(glm::radians(60.0f), (float)winSize.x / (float)winSize.y, 0.1f, 100.0f);
	glm::vec3 cameraPos(0.0f, 0.0f, 10.0f);
	glm::vec3 target(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	mViewMat = glm::lookAt(cameraPos, target, up);
}
Ray Camera::GetRay(glm::ivec2 windowPos, glm::ivec2 winSize)
{

	Ray ray;
	glm::vec4 nearWinPlane;
	nearWinPlane.x = (((float)windowPos.x / (float)winSize.x) * 2.0f) - 1.0f;
	nearWinPlane.y = (((float)windowPos.y / (float)winSize.y) * 2.0f) - 1.0f;
	nearWinPlane.z = -1.0f;
	nearWinPlane.w = 1.0f;

	glm::vec4 farWinPlane = nearWinPlane;
	farWinPlane.z = 1.0f;

	glm::vec4 nearSomething;
	glm::vec4 farSomething;

	nearSomething = (nearWinPlane * glm::inverse(mProjMat));
	nearSomething = nearSomething / nearSomething.w;

	farSomething = (farWinPlane * glm::inverse(mProjMat));
	farSomething = farSomething / farSomething.w;


	nearSomething = nearSomething * glm::inverse(mViewMat);
	farSomething = farSomething * glm::inverse(mViewMat);

	glm::vec3 nearPlaneVec3 = nearSomething;
	glm::vec3 farPlaneVec3 = farSomething;

	ray.mDirection = glm::normalize(farPlaneVec3 - nearPlaneVec3);
	//std::cout << "NearPlane: " << nearPlaneVec3.x << "," << nearPlaneVec3.y << "," << nearPlaneVec3.z << std::endl;


	//std::cout << "FarPlane: " << farPlaneVec3.x << "," << farPlaneVec3.y << "," << farPlaneVec3.z << std::endl;
	ray.mOrigin = glm::vec3(nearPlaneVec3);

	return ray;
}