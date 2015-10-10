#include "Camera.h"
#include "variables.h"

Ray Camera::GenerateRay(vec2 sample) {
	vec3 w = normalize(eyeinit - center);
	vec3 u = cross(upinit, w);
	u = normalize(u);
	vec3 v = cross(w, u);
	float alpha, beta;
	beta = tan(fovy / 2) * (Height / 2 - sample.y) / (Height / 2);
	alpha = tan(fovy / 2) * (sample.x - (Width / 2)) / (Width / 2) * Width / Height;
	Ray cameraRay(eyeinit, normalize(alpha * u - beta * v - w));
	return cameraRay;
}