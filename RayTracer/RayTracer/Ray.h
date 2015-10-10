#ifndef RAY_HEADER
#define RAY_HEADER

#include "Headers.h"

class Ray {
public:
	vec3 pos;
	vec3 dir;
	Ray(vec3 position = vec3(0, 0, 0), vec3 direction = vec3(0, 0, 0));
};

#endif