#include "Raytracer.h"

glm::vec3 Raytracer::TraceRay(Ray ray)
{
	glm::vec3 PixelColour(0.3f, 0.3f, 0.3f);
	glm::vec3 CloseCollidePosition;

	float CloseDepth = 10000000.0f;

	for (int i = 0; i < sphere.size(); i++)
	{
		glm::vec3 CollidePosition;

		if(sphere[i]->RayCollide(ray,CollidePosition))
		{
			float Depth = glm::length(CollidePosition - ray.mOrigin);
			if (Depth < CloseDepth)
			{
				CloseDepth = Depth;
				CloseCollidePosition = CollidePosition;
				PixelColour = sphere[i]->ShadePosition(CollidePosition);
			}
		}

	}

	return PixelColour;

}