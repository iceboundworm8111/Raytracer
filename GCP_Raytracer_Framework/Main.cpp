
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
#include <random>

void PixelDraw(glm::ivec2 winSize, Camera* _maincamera, Raytracer* _raytracer, GCP_Framework* _myFrameWork,int startRow,int endRow)
{
	float samples = 16.0f;
	/*float jitterMatrix[4 * 2] = 
	{
	   -0.25, 0.75,
		0.75,  0.25,
	   -0.75, -0.25,
		0.25, -0.75,
	};*/
	float jitterMatrix[4 * 2] = {
	-1.0 / 4.0,  3.0 / 4.0,
	 3.0 / 4.0,  1.0 / 3.0,
	-3.0 / 4.0, -1.0 / 4.0,
	 1.0 / 4.0, -3.0 / 4.0,
	};

	//This function will draw the pixels to the screen
	for (int y = 0; y < winSize.y; y++)
	{
		for (int x = startRow; x < endRow; x++)
		{
			glm::vec3 colour (0);
		
				for (int i = 0; i < samples; i++)
				{

					Ray ray = _maincamera->GetRay(glm::vec2(x + jitterMatrix[2*i], y + jitterMatrix[(2*i)+1]), winSize);
					colour += _raytracer->TraceRay(ray, 0);

				}
			// divide by number of samples
			colour /= samples;
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



	std::random_device rd;  // Seed for the random number engine
	std::mt19937 gen(rd()); // Mersenne Twister random number engine
	std::uniform_real_distribution<> dis(0.0, 1.0); // Distribution in range [0.0, 1.0]

	float randomDecimal = dis(gen);
	// Set window size
	glm::ivec2 winSize(920,680);

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
	for (int i = 0; i <= 20; i++)
	{
		randomPosZ = rand() % 61 - 70; // random number between -70 and -10
		randomPosY = rand() % 36 - 15; // random number between -10 and 20
		randomPosX = rand() % 61 - 30; // random number between -30 and 30
		float randomColR = dis(gen);
		float randomColG = dis(gen);
		float randomColB =  dis(gen);
		randomRad = rand() % 5;
		// Sphere - Position (left/right(-left, +right), up/down(+up, -down), forward/back(-back, +forward)), Colour, Radius
		Sphere* sphere = new Sphere(glm::vec3(randomPosX, randomPosY, randomPosZ), glm::vec3(randomColR, randomColG, randomColB),3);
		sphere->mReflectivity = 0.5f;
		raytracer.objects.push_back(sphere);
	}


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
