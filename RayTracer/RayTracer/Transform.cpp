#include "Transform.h"
mat3 dotproduct(vec3 u, vec3 v)
{
	return glm::mat3(u.x * v, u.y * v, u.z * v);
}

mat3 Transform::rotate(const float degrees, const vec3& axis)
{
	mat3 ret;
	float angle = glm::radians(degrees);
	glm::mat3 Identity(1.0);
	glm::mat3 M = dotproduct(axis, axis);
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	glm::mat3 Astar(0, z, -y, -z, 0, x, y, -x, 0);
	ret = cos(angle) * Identity + (1 - cos(angle)) * M + sin(angle) * Astar;
	return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
	mat4 ret;
	ret = glm::mat4(vec4(sx, 0, 0, 0), vec4(0, sy, 0, 0), vec4(0, 0, sz, 0), vec4(0, 0, 0, 1));
	return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
	mat4 ret;
	ret = glm::mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(tx, ty, tz, 1));
	return ret;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}

vec3 upvector(const vec3 &up, const vec3 & zvec)
{
	vec3 x = glm::cross(up, zvec);
	vec3 y = glm::cross(zvec, x);
	vec3 ret = glm::normalize(y);
	return ret;
}

vec3 pointTrans(vec3 oldvec, mat4 transmat) {
	vec4 newvec = vec4(oldvec, 1);
	newvec = transmat * newvec;
	return vec3(newvec[0], newvec[1], newvec[2]);
}

vec3 vecTrans(vec3 oldvec, mat4 transmat) {
	vec4 newvec = vec4(oldvec, 0);
	newvec = transmat * newvec;
	return vec3(newvec[0], newvec[1], newvec[2]);
}