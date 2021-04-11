#pragma once
#ifndef OBJECT_H
#define OBJECT_H
#include "ray.h"
#include "tools.h"
#include "vec3.h"
class Sphere :public hittable
{
public:
	Point3 center;
	double radiu;
    std::shared_ptr<material> mat_ptr;
    Sphere() {};
	Sphere(Point3 a, double r,std::shared_ptr<material> m) :center(a), radiu(r),mat_ptr(m) {};

	virtual bool hit(const ray& r, double min, double max, hit_record& rec)const override;


};
bool Sphere::hit(const ray& r, double min, double max, hit_record& rec)const
{
    vec3 oc = r.origin - center;
    auto a = dot(r.vect, r.vect);
    auto half_b = dot(oc, r.vect);
    auto c = dot(oc, oc) - radiu * radiu;
    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
    {
        return false;
    }
    auto temp = sqrt(discriminant);
    auto t = (-half_b - temp) / a;
    if (t<min || t>max)
    {
        t= (-half_b + temp) / a;
        if (t<min || t>max)
        {
            return false;
        }
    }
    rec.t = t;
    rec.p = r.at(rec.t);

    vec3 outnormal =(rec.p - center) / radiu; 
    rec.set_face_normal(r, outnormal);
    rec.normal = outnormal;
    rec.mat_ptr = mat_ptr;
    return true;
}

class lambertian :public material
{
public:
    lambertian(const color& a) :albedo(a) {}
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered, bool& islight
    )const override {
        auto scatter_dir = random_in_hemisphere(rec.normal);
        if (scatter_dir.near_zero())
            scatter_dir = rec.normal;
        islight = false;
        scattered = ray(rec.p, scatter_dir);
        attenuation = albedo;
        return true;
    }
    color albedo;
};

class metal :public material {
public:
    metal(const color& a,double f) :albedo(a),fuzz(f<1?f:1) {}
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered, bool& islight
    )const override {
        vec3 temp=unit_vector(r_in.vect);
        vec3 reflected = reflect(temp, rec.normal);
        islight = false;
        scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.vect,rec.normal)>0);
    }
    color albedo;
    double fuzz;
};

class Light:public material
{
public:
    Light(color lled) :led(lled){};
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered, bool& islight
    )const override {
        islight = true;
        attenuation = led;
        return true;
    }
    color led;
   

};
#endif