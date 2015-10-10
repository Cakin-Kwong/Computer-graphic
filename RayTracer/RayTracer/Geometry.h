#ifndef GEOMETRY_HEADER
#define GEOMETRY_HEADER

#include "Ray.h"
#include "LocalGeo.h"


class Shape {
public:
	float ambient[3];
	float diffuse[3];
	float specular[3];
	float emission[3];
	float shininess;
	mat4 transform;
	virtual bool intersect(Ray& ray, float* thit, LocalGeo* local) = 0;
	void setBRDF(float* ka, float* kd, float* ks);
	bool virtual intersectPD(Ray& ray, float tmax) = 0;
};

class Sphere :public Shape {
public:
	vec3 pos;
	float radius;
	Sphere(vec3 center, float Radius);
	bool intersect(Ray& ray, float* thit, LocalGeo* local);
	bool intersectPD(Ray& ray, float tmax);
};

class Triangle :public Shape {
public:
	vec3 Apos;
	vec3 Bpos;
	vec3 Cpos;
	vec3 normal;
	Triangle(vec3 A, vec3 B, vec3 C);
	bool intersect(Ray& ray, float* thit, LocalGeo* local);
	void solve(vec3 Point, float* beta, float* gama);
	bool intersectPD(Ray& ray, float tmax);
};

#endif