#pragma once
#ifndef _VEC3_H
#define _VEC3_H
#include <vector>


class vec3
{
public:
	friend vec3 operator/(vec3 a, double b);
	friend vec3 operator-(const vec3& a, const vec3& b);
	friend vec3 operator+(const vec3& a, const vec3& b);
	friend vec3 operator*(const vec3& a, const vec3& b);
	friend vec3 operator*(double a, const vec3& b);
	double dot(const vec3& a, const vec3& b);
	vec3 cross(const vec3& a, const vec3& b);
	double length_squared() const
	{
		return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	}
	double length() const
	{
		return sqrt(length_squared());
	}
	friend vec3 unit_vector(vec3 v) {
		return v / v.length();
	}
	double v[3];
	vec3();
	vec3(double _x, double _y, double _z);
	vec3(const vec3& other);
	vec3& operator=(const vec3& a);
	vec3& operator+=(const vec3& a);
	vec3& operator*=(double value);
	vec3& operator-=(const vec3& a);
	vec3& operator/= (const double a);
	vec3 operator-() const { return vec3(-v[0], -v[1], -v[2]); }
	double operator[](int i)const { return v[i]; }
	double& operator[](int i) { return v[i]; }
	bool near_zero() const {
		const auto s = 1e-8;
		return (fabs(v[0]) < s) && (fabs(v[1]) < s) && (fabs(v[2]) < s);
	}
};
using Point3 = vec3;
using color = vec3;
vec3 operator/(vec3 a, double b)
{
	return (1 / b) * a;
}
vec3 cross(const vec3& a, const vec3& b)
{
	return vec3(a.v[1] * b.v[2] - a.v[2] * b.v[1],
		a.v[2] * b.v[0] - a.v[0] * b.v[2],
		a.v[0] * b.v[1] - a.v[1] * b.v[0]);
}
double dot(const vec3& a, const vec3& b)
{
	return a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2];
}

vec3& vec3::operator/= (const double a)
{
	return *this *= 1 / a;
}
vec3 operator-(const vec3& a, const vec3& b)
{
	return vec3(a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2]);
}
vec3 operator+(const vec3& a, const vec3& b)
{
	return vec3(a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2]);
}
vec3 operator*(const vec3& a, const vec3& b)
{
	return vec3(a.v[0] * b.v[0], a.v[1] * b.v[1], a.v[2] * b.v[2]);
}
vec3 operator*(double a, const vec3& b)
{
	return vec3(a * b.v[0], a * b.v[1], a * b.v[2]);
}
vec3::vec3(double _x, double _y, double _z)
{
	v[0] = _x;
	v[1] = _y;
	v[2] = _z;
}
vec3::vec3()
{
	v[0] = 0; v[1] = 0; v[2] = 0;
}
vec3::vec3(const vec3& other)
{
	v[0] = other.v[0];
	v[1] = other.v[1];
	v[2] = other.v[2];
}
vec3& vec3::operator=(const vec3& a)
{
	v[0] = a.v[0];
	v[1] = a.v[1];
	v[2] = a.v[2];
	return *this;
}
vec3& vec3::operator+=(const vec3& a)
{
	v[0] += a.v[0];
	v[1] += a.v[1];
	v[2] += a.v[2];
	return *this;
}
vec3& vec3::operator-=(const vec3& a)
{
	v[0] -= a.v[0];
	v[1] -= a.v[1];
	v[2] -= a.v[2];
	return *this;
}
vec3& vec3::operator*=(double a)
{
	v[0] *= a;
	v[1] *= a;
	v[2] *= a;
	return *this;
}


#endif