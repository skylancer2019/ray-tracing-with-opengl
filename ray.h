#pragma once
#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include <memory>
class ray
{
public:
	ray() {};
	ray(const Point3& _origin, const vec3& _vect) :origin(_origin), vect(_vect) {}

	Point3 origin;
	vec3 vect;
	Point3 at(double t)const
	{
		return origin + t * vect;
	}
};
class material;
struct hit_record
{
	Point3 p;
	vec3 normal;
	std::shared_ptr<material> mat_ptr;
	double t;
	bool front_face;
	void set_face_normal(const ray& r, const vec3& outward)
	{
		if (dot(r.vect, outward) < 0)
		{
			front_face = true;
			normal = outward;
		}
		else
		{
			front_face = false;
			normal = -outward;
		}
	}
};
class material
{
public:
	virtual bool scatter(
		const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered,bool& islight
	)const = 0;
};
//交点性质


class hittable
{
public:
	virtual bool hit(const ray& r, double min, double max, hit_record& rec) const = 0;
};





#endif