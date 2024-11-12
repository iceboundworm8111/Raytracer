
#include "GCP_GFX_Framework.h"
#include "Ray.h"
#include "Camera.h"
#include "Raytracer.h"
#include "Sphere.h"
#include "Plane.h"


int main(int argc, char* argv[])
{
	// Set window size
	glm::ivec2 winSize(640,480);

	// This will handle rendering to screen
	GCP_Framework _myFramework;

	// Initialises SDL and OpenGL and sets up a framebuffer
	if (!_myFramework.Init(winSize))
	{
		return -1;
	}

	Raytracer raytracer;
	Camera maincamera(glm::ivec2(winSize.x, winSize.y));

	glm::vec3 colour(1, 0, 0);

	Sphere* sphere1 = new Sphere(glm::vec3(0, 0, -50), glm::vec3(0.0, 0.0, 1.0), 1);
	raytracer.object.push_back(sphere1);
	Sphere* sphere2 = new Sphere(glm::vec3(-1,0, -50), glm::vec3(1.0, 0.0, 0.0), 1);
	raytracer.object.push_back(sphere2);
	Plane* plane1 = new Plane(glm::vec3(0, -2, 0), glm::vec3(0, 1, 0), glm::vec3(0.3f, 0.3f, 0.3f));
	raytracer.object.push_back(plane1);
	Plane* plane2 = new Plane(glm::vec3(0, 0, -50), glm::vec3(0, 0, 1), glm::vec3(0.3f, 0.3f, 0.3f));
	raytracer.object.push_back(plane2);
	
	
	for (int y = 0; y < winSize.y; y++)
	{
		for (int x = 0; x < winSize.x; x++)
		{

			Ray ray = maincamera.GetRay(glm::ivec2(x, y),glm::ivec2(winSize.x,winSize.y));
			colour = raytracer.TraceRay(ray);
			_myFramework.DrawPixel(glm::ivec2(x, y), colour);

		}
	}


	// Pushes the framebuffer to OpenGL and renders to screen
	// Also contains an event loop that keeps the window going until it's closed
	_myFramework.ShowAndHold();
	return 0;


}
