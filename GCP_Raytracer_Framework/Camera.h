#pragma once

#include <GLM/glm.hpp>
class Camera
{
public:
	Camera();
	~Camera();
private:
	glm::mat4 mView;
	glm::mat4 mProj;
};