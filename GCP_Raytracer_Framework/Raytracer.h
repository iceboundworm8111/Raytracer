#pragma once
#include "Ray.h"
#include "BaseObject.h"
#include "Light.h"
#include <GLM/glm.hpp>
#include <vector>


class Raytracer
{
public:
	glm::vec3 TraceRay(Ray ray, int _depth);//Function to trace the ray
	std::vector<BaseObject*> objects;//Vector of objects
	std::vector<Light*> lights;//Vector of lights
};