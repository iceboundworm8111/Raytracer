#include "Raytracer.h"
#include "Timer.h"
#include <iostream>

glm::vec3 Raytracer::TraceRay(Ray ray, int _depth)
{
	//ScopedTimer Timer("TraceRay Timer");
	glm::vec3 PixelColour{ 0.0f };
	glm::vec3 CloseCollidePosition(0.0f, 0.0f, 0.0f);

	float CloseDepth = 10000000.0f;
	BaseObject* ClosestObject = nullptr;
	for (int i = 0; i < objects.size(); i++)
	{
		glm::vec3 CollidePosition;
		if (objects[i]->RayCollide(ray, CollidePosition))
		{
			float Depth = glm::length(CollidePosition - ray.mOrigin);
			if (Depth < CloseDepth)
			{
				//Depth perception is the ability to see things in three dimensions (including length, width and depth), and to judge how far away an object is. 
				//Depth perception is made possible by monocular (one eye) and binocular (two eyes) cues.
				CloseDepth = Depth;
				CloseCollidePosition = CollidePosition;
				ClosestObject = objects[i];
			}
		}
	}

	if (ClosestObject == nullptr)
	{
		return PixelColour;
	}
	for (int i = 0; i < lights.size(); i++)
	{
		bool shadow = false;

		for (int j=0; j < objects.size(); j++)
		{
			glm::vec3 ShadowCollidePosition;

			glm::vec3 ShadowRayDirection = CloseCollidePosition + (ClosestObject->NormalPosition(CloseCollidePosition) * 0.001f);

			if (objects[j]->RayCollide(Ray(ShadowRayDirection, glm::normalize(lights[i]->mPosition - CloseCollidePosition)), ShadowCollidePosition))
			{
				if (glm::length(ShadowCollidePosition - CloseCollidePosition) < glm::length(lights[i]->mPosition - CloseCollidePosition))
				{
					shadow = true;
					break;
				}
			}
		}

		if (!shadow)
		{
			PixelColour += ClosestObject->ShadePosition(CloseCollidePosition, lights[i]->mPosition, lights[i]->mColour, ray.mOrigin);
		}
	}

	//Reflection
	if (_depth < 3 && ClosestObject->mReflectivity >0.01f)
	{
		glm::vec3 ReflectDir = glm::reflect(ray.mDirection, ClosestObject->NormalPosition(CloseCollidePosition));
		Ray ReflectRay(CloseCollidePosition + (ClosestObject->NormalPosition(CloseCollidePosition) *0.001f), ReflectDir);

		glm::vec3 ReflectColour = TraceRay(ReflectRay, _depth + 1);
		PixelColour = PixelColour + (ReflectColour * ClosestObject->mReflectivity);

	}	
	return PixelColour;
}