#pragma once

#include "vec3.h"

#include "iostream"

using Color = vec3;

inline double linear_to_gamma(double linear_component)
{
	return sqrt(linear_component);
}

inline void write_color(std::ostream& out, Color pixel_color, int samples_per_pixel)
{
	double r = pixel_color.x();
	double g = pixel_color.y();
	double b = pixel_color.z();

	// Divide the color by the number of samples
	double scale = 1.0 / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;

	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);

	// Write the translated [0,255] value of each color component
	static const Interval intensity(0.000, 0.999);
	out << static_cast<int>(255.999 * intensity.clamp(r)) << ' ' << static_cast<int>(255.999 * intensity.clamp(g)) << ' ' << static_cast<int>(255.999 * intensity.clamp(b)) << '\n';
}