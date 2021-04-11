#pragma once
#ifndef TOOLS_H
#define TOOLS_H
#include <cstdlib>
#include "vec3.h"
//工具函数头
double random_double()
{
	return rand() / (RAND_MAX + 1.0);
}
double random_double(double min, double max)
{
	return min + (max - min) * rand()/(RAND_MAX+1.0);
}
vec3 vec3Random(double min, double max)
{
	return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}
double clamp(double x, double min, double max)
{
	if (x < min)
	{
		return min;
	}
	else
	{
		if (x > max)
		{
			return max;
		}
		return x;
	}
}


vec3 random_in_unit_sphere()
{
	while (true)
	{
		auto p = vec3Random(-1, 1);
		if (p.length_squared() >= 1)continue;
		return p;
	}
}
/*
返回反射光线
*/
vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) * n;
}

vec3 random_in_hemisphere(const vec3& normal) {
	vec3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}
#endif // !TOOLS_H
