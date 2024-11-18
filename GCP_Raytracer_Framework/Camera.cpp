#include "Camera.h"
#include "Timer.h"
#include <glm/gtc/matrix_transform.hpp>
#include<iostream>

Camera::Camera(glm::ivec2 winSize)
{
	mProjMat = glm::perspective(glm::radians(45.0f), (float)winSize.x / (float)winSize.y, 0.1f, 100.0f);

	glm::vec3 cameraPos(0.0f, 0.0f, 10.0f);
	glm::vec3 target(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	mViewMat = glm::lookAt(cameraPos, target, up);
}
Ray Camera::GetRay(glm::ivec2 windowPos, glm::ivec2 winSize)
{
	//ScopedTimer Timer("GetRay");
	Ray ray;

	glm::vec4 nearPoint;
	glm::vec4 farPoint;

	nearPoint.x = float(windowPos.x) / float(winSize.x) * 2 - 1;
	nearPoint.y = float(windowPos.y) / float(winSize.y) * 2 - 1;
	nearPoint.z = -1;
	nearPoint.w = 1;

	farPoint = nearPoint;
	farPoint.z = 1;

	glm::vec4 nearView = glm::inverse(mProjMat) * nearPoint;
	glm::vec4 farView = glm::inverse(mProjMat) * farPoint;

	nearView = nearView / nearView.w;
	farView = farView / farView.w;

	nearView = glm::inverse(mViewMat) * nearView;
	farView = glm::inverse(mViewMat) * farView;


	ray.mOrigin = glm::vec3(nearView);
	ray.mDirection = glm::normalize(glm::vec3(farView - nearView));



	return ray;
}