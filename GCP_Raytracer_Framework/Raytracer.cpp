#include "Raytracer.h"


glm::vec3 Raytracer::TraceRay(Ray ray)
{
	
	for (int i = 0; i < sphere.size(); i++)
	{
		glm::vec3 CollidePosition;
		if(sphere[i]->RayCollide(ray,CollidePosition))
		{
			return sphere[i]->ShadePosition(CollidePosition);
		}

	}

	return glm::vec3(0.3f, 0.3f, 0.3f);

}