#include "Raytracer.h"
#include "Timer.h"
#include <iostream>

glm::vec3 Raytracer::TraceRay(Ray ray)
{
	//ScopedTimer Timer("TraceRay Timer");
	glm::vec3 PixelColour(0.3f, 0.3f, 0.3f);
	glm::vec3 CloseCollidePosition;

	float CloseDepth = 10000000.0f;
	
	for (int i = 0; i < object.size(); i++)
	{
		glm::vec3 CollidePosition;
		if(object[i]->RayCollide(ray,CollidePosition))
		{
			float Depth = glm::length(CollidePosition - ray.mOrigin);
			if (Depth < CloseDepth)
			{
				CloseDepth = Depth;
				CloseCollidePosition = CollidePosition;
				PixelColour = object[i]->ShadePosition(CollidePosition);
			}
		}

	}

	return PixelColour;

}