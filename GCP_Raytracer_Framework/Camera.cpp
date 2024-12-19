#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include<iostream>

Camera::Camera(glm::ivec2 winSize)
{
	//Setting the projection matrix
	mProjMat = glm::perspective(glm::radians(60.0f), (float)winSize.x / (float)winSize.y, 0.1f, 100.0f);

	mViewMat = glm::mat4{ 1.f };
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	//Set up the view matrix
	mViewMat = glm::rotate(mViewMat, glm::radians(rotation.x), glm::vec3(1, 0, 0));//Rotate the view matrix on the x-axis
	mViewMat = glm::rotate(mViewMat, glm::radians(rotation.y), glm::vec3(0, 1, 0));//Rotate the view matrix on the y-axis
	mViewMat = glm::rotate(mViewMat, glm::radians(rotation.z), glm::vec3(0, 0, 1));//Rotate the view matrix on the z-axis
	mViewMat = glm::translate(mViewMat, position);//Translate the view matrix
}
Ray Camera::GetRay(glm::vec2 windowPos, glm::ivec2 winSize)
{

	Ray ray;

	glm::vec4 nearPoint;
	glm::vec4 farPoint;

	nearPoint.x = float(windowPos.x) / float(winSize.x) * 2 - 1;
	nearPoint.y = float(windowPos.y) / float(winSize.y) * 2 - 1;
	nearPoint.z = -1;
	nearPoint.w = 1;

	farPoint = nearPoint;
	farPoint.z = 1;

	glm::vec4 nearView = glm::inverse(mProjMat) * nearPoint;//Inverse of the projection matrix multiplied by the near point
	glm::vec4 farView = glm::inverse(mProjMat) * farPoint;//Inverse of the projection matrix multiplied by the far point

	nearView = nearView / nearView.w;
	farView = farView / farView.w;

	nearView = glm::inverse(mViewMat) * nearView;
	farView = glm::inverse(mViewMat) * farView;


	ray.mOrigin = glm::vec3(nearView);//Sets the origin of the ray
	ray.mDirection = glm::normalize(glm::vec3(farView - nearView));//Sets the direction of the ray



	return ray;
}