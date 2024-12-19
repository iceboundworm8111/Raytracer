#include "Raytracer.h"
#include <iostream>

glm::vec3 Raytracer::TraceRay(Ray ray, int _depth)
{
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
				//Depth perception is the ability to see things in three dimensions
				CloseDepth = Depth;
				CloseCollidePosition = CollidePosition;
				ClosestObject = objects[i];
			}
		}
	}

	if (ClosestObject == nullptr)//If there is no object return the pixel colour
	{
		return PixelColour;
	}
	for (int i = 0; i < lights.size(); i++)//For each light in the scene calculate the pixel colour and the shadow of the object 
	{
		bool shadow = false;

		for (int j=0; j < objects.size(); j++)
		{
			glm::vec3 ShadowCollidePosition;

			glm::vec3 ShadowRayDirection = CloseCollidePosition + (ClosestObject->NormalPosition(CloseCollidePosition) * 0.001f);//Shadow ray direction is the position of the object plus the normal of the object times 0.001f

			if (objects[j]->RayCollide(Ray(ShadowRayDirection, glm::normalize(lights[i]->mPosition - CloseCollidePosition)), ShadowCollidePosition)) //If the shadow ray collides with an object set the shadow to true
			{
				if (glm::length(ShadowCollidePosition - CloseCollidePosition) < glm::length(lights[i]->mPosition - CloseCollidePosition))//If the length of the shadow collide position minus the close collide position is less than the length of the light position minus the close collide position
				{
					shadow = true;
					break;
				}
			}
		}

		if (!shadow)
		{
			PixelColour += ClosestObject->ShadePosition(CloseCollidePosition, lights[i]->mPosition, lights[i]->mColour, ray.mOrigin);//If there is no shadow calculate the pixel colour
		}
	}

	//Reflection
	if (_depth < 3 && ClosestObject->mReflectivity >0.01f)//If the depth is less than 3 and the reflectivity is greater than 0.01f calculate the reflection
	{
		glm::vec3 ReflectDir = glm::reflect(ray.mDirection, ClosestObject->NormalPosition(CloseCollidePosition));//Reflect direction is the reflection of the direction of the ray and the normal of the object
		Ray ReflectRay(CloseCollidePosition + (ClosestObject->NormalPosition(CloseCollidePosition) * 0.001f), ReflectDir);//Reflect ray is the close collide position plus the normal of the object times 0.001f and the reflect direction

		glm::vec3 ReflectColour = TraceRay(ReflectRay, _depth + 1);//Reflect colour is the trace ray of the
		PixelColour = PixelColour + (ReflectColour * ClosestObject->mReflectivity);//Pixel colour is the pixel colour plus the reflect colour times the reflectivity of the object

	}	
	return PixelColour;
}