#include <iostream>

#include "hittable-list.h"
#include "sphere.h"
#include "camera.h"

int main()
{
	// World
	HittableList world;
	world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

	// Camera
	Camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 400;
}