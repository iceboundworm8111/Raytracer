
#include "GCP_GFX_Framework.h"
#include "Ray.h"
#include "Camera.h"
#include "Raytracer.h"
#include "Sphere.h"
#include "Plane.h"
#include "Light.h"
#include "Timer.h"
#include <random>
#include <thread>

void PixelDraw(glm::ivec2 winSize, Camera* _maincamera, Raytracer* _raytracer, GCP_Framework* _myFrameWork,int startRow,int endRow)
{
	//This function will draw the pixels to the screen
	for (int y = 0; y < winSize.y; y++)
	{
		for (int x = startRow; x < endRow; x++)
		{
			Ray ray = _maincamera->GetRay(glm::ivec2(x,y), winSize);
			glm::vec3 colour = _raytracer->TraceRay(ray);
			_myFrameWork->DrawPixel(glm::ivec2(x,y), colour);


		}
	}
}
//This function will create the threads and assign the pixel drawing to them
void ThreadRays(int _numOfThreads, glm::vec2 _winSize, Raytracer* _rayTracer, Camera* _camera, GCP_Framework* _myFrameWork)
{
	//Creation of the vector which contains the threads
	std::vector<std::thread> threads;
	int xRows = _winSize.x / _numOfThreads; //Divides the screen on the x-axis by the number threads
	//This will create the threads and assign the pixel drawing to them
	for (int i = 0; i < _numOfThreads; i++)
	{
		int xStart = i * xRows;
		int xEnd = (i + 1) * xRows;
		if (i == _numOfThreads - 1)
		{
			xEnd = _winSize.x;
		}
		else
		{
			xEnd = (i + 1) * xRows;
		}
		threads.push_back(std::thread(PixelDraw, _winSize, _camera, _rayTracer, _myFrameWork,xStart,xEnd)); //Emplace is better?
	}
	for (int i = 0; i < _numOfThreads; i++)
	{
		threads[i].join();
	}
	
}

int main(int argc, char* argv[])
{
	float randomPosZ = 0.0f;
	float randomPosY = 0.0f;
	float randomPosX = 0.0f;

	float randomColR = 0.0f;
	float randomColG = 0.0f;
	float randomColB = 0.0f;

	float randomRad = 0.0f;

	randomPosZ = rand() % 70;


	randomRad = rand() % 5;
	// Set window size
	glm::ivec2 winSize(640,480);

	// This will handle rendering to screen
	GCP_Framework _myFramework;

	// Initialises SDL and OpenGL and sets up a framebuffer
	if (!_myFramework.Init(winSize))
	{
		return -1;
	}
	//Initialises the raytracer and the camera
	Raytracer raytracer;
	Camera maincamera(glm::ivec2(winSize.x, winSize.y));
	

	//Creation of the objects and the planes
	// Sphere - Position (left/right(-left, +right), up/down(+up, -down), forward/back(-back, +forward)), Colour, Radius
	Sphere* sphere1 = new Sphere(glm::vec3(-20, 0, -randomPosZ), glm::vec3(0.0, 0.0, 1.0), randomRad);
	raytracer.objects.push_back(sphere1);
	Sphere* sphere2 = new Sphere(glm::vec3(5,5, -randomPosZ), glm::vec3(1.0, 0.0, 0.0), randomRad);
	raytracer.objects.push_back(sphere2);
	Sphere* sphere3 = new Sphere(glm::vec3(-30, 15, -randomPosZ), glm::vec3(0.5, 0.5, 1.0), randomRad);
	raytracer.objects.push_back(sphere3);
	Sphere* sphere4 = new Sphere(glm::vec3(20, -5, -randomPosZ), glm::vec3(1.0, 0.0, 0.8), randomRad);
	raytracer.objects.push_back(sphere4);
	Sphere* sphere5 = new Sphere(glm::vec3(0, 0, -randomPosZ), glm::vec3(0.8, 1.0, 1.0), randomRad);
	raytracer.objects.push_back(sphere5);
	Sphere* sphere6 = new Sphere(glm::vec3(0, -10, -randomPosZ), glm::vec3(1.0, 1.0, 0.0), randomRad);
	raytracer.objects.push_back(sphere6);

	// Plane - Position (left/right(-left, +right), up/down(+up, -down), forward/back(-back, +forward)), Normal, Colour
	Plane* floor = new Plane(glm::vec3(0, -15, 50), glm::vec3(0, 1, 0), glm::vec3(1.0f, 1.0f, 1.0f));
	raytracer.objects.push_back(floor);
	Plane* wall = new Plane(glm::vec3(0, 0, -70), glm::vec3(0, 0, 1), glm::vec3(1.0f, 1.0f, 1.0f));
	raytracer.objects.push_back(wall);

	//Creation of the light
	// Lights - Position (left/right(-left, +right), up/down(+up, -down), forward/back(-back, +forward)), Colour
	Light* llight = new Light(glm::vec3(-40, 0, -30), glm::vec3(1.0f, 1.0f, 1.0f));
	raytracer.lights.push_back(llight);
	Light* rlight = new Light(glm::vec3(45, 10, -30), glm::vec3(1.0f, 1.0f, 1.0f));
	raytracer.lights.push_back(rlight);

	//Number of threads
	int NumberOfThreads = 32;
	{
		//Fastest time in debug was 0.21998 seconds with 32 threads (shadows,specular, diffuse)
		ScopedTimer Timer("Main Loop");
		ThreadRays(NumberOfThreads, glm::vec2(winSize.x, winSize.y), &raytracer, &maincamera, &_myFramework);
	}

	


	// Pushes the framebuffer to OpenGL and renders to screen
	// Also contains an event loop that keeps the window going until it's closed
	_myFramework.ShowAndHold();
	return 0;


}
