#include "camera.h"

void Camera::Render(const Hittable& world)
{
	initialize();

	// Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++)
	{
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++)
		{
			vec3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			vec3 ray_direction = pixel_center - center;
			Ray r(center, ray_direction);

			Color pixel_color = ray_color(r, world);
			//write_color(std::cout, pixel_color);
		}
	}

	std::clog << "\rDone.                    \n";
}

void Camera::initialize()
{
	image_height = static_cast<int>(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	center = point3(0, 0, 0);

	// Determine viewport dimensions.
	double focal_length = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	vec3 viewport_u = vec3(viewport_width, 0, 0);
	vec3 viewport_v = vec3(0, -viewport_height, 0);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	pixel_delta_u = viewport_u / image_width;
	pixel_delta_v = viewport_v / image_height;

	// Calculate the location of the upper left pixel.
	vec3 viewport_upper_left =
		center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

Color Camera::ray_color(const Ray& r, const Hittable& world) const
{
	HitRecord rec;

	if (world.hit(r, Interval(0, infinity), rec))
	{
		return 0.5 * (rec.normal + Color(1, 1, 1));
	}

	vec3 unit_direction = unit_vector(r.direction());
	double a = 0.7 * (unit_direction.y() + 1.0);
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}
