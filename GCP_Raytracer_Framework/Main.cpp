
#include "GCP_GFX_Framework.h"
#include "Ray.h"
#include "Camera.h"
#include "Raytracer.h"
#include "Sphere.h"
#include "Plane.h"
#include "Timer.h"
#include <thread>

void PixelDraw(glm::ivec2 winSize, Camera* _maincamera, Raytracer* _raytracer, GCP_Framework* _myFrameWork)
{


	for (int y = 0; y < winSize.y; y++)
	{
		for (int x = 0; x < winSize.x; x++)
		{
			Ray ray = _maincamera->GetRay(glm::ivec2(x,y), winSize);
			glm::vec3 colour = _raytracer->TraceRay(ray);
			_myFrameWork->DrawPixel(glm::ivec2(x,y), colour);


		}
	}
}

void ThreadRays(int _numOfThreads, glm::vec2 _winSize, Raytracer* _rayTracer, Camera* _camera, GCP_Framework* _myFrameWork)
{
	std::vector<std::thread> threads;

	for (int i = 0; i < _winSize.x ; i++)
	{
		//threads.emplace_back(PixelDraw(_winSize, _rayTracer,_camera,_myFrameWork));
	}
}

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
	


	Sphere* sphere1 = new Sphere(glm::vec3(0, 0, 0), glm::vec3(0.0, 0.0, 1.0), 1);
	raytracer.object.push_back(sphere1);
	Sphere* sphere2 = new Sphere(glm::vec3(-1,0, 0), glm::vec3(1.0, 0.0, 0.0), 1);
	raytracer.object.push_back(sphere2);
	Plane* plane1 = new Plane(glm::vec3(0, -2, 0), glm::vec3(0, 1, 0), glm::vec3(0.3f, 0.3f, 0.3f));
	raytracer.object.push_back(plane1);
	Plane* plane2 = new Plane(glm::vec3(0, 0, -25), glm::vec3(0, 0, 1), glm::vec3(0.3f, 0.3f, 0.3f));
	raytracer.object.push_back(plane2);
	



	// Pushes the framebuffer to OpenGL and renders to screen
	// Also contains an event loop that keeps the window going until it's closed
	_myFramework.ShowAndHold();
	return 0;


}
