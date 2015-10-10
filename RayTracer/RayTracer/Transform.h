#ifndef TRANSFORM_HEADER
#define TRANSFORM_HEADER

#include "Headers.h"

class Transform
{
public:
	Transform();
	virtual ~Transform();
	static mat3 rotate(const float degrees, const vec3& axis);
	static mat4 scale(const float &sx, const float &sy, const float &sz);
	static mat4 translate(const float &tx, const float &ty, const float &tz);
};
vec3 upvector(const vec3 &up, const vec3 & zvec);
vec3 pointTrans(vec3 oldvec, mat4 transmat);
vec3 vecTrans(vec3 oldvec, mat4 transmat);
#endif