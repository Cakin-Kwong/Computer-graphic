#include "Lights.h"

DirectionalLight::DirectionalLight(vec3 dir, vec3 color) {
	ldir = dir;
	lcol = color;
}

void DirectionalLight::generateLightRay(LocalGeo& local, Ray* lray, vec3* lcolor) {
	*lray = Ray(local.pos, ldir);
	*lcolor = lcol;
}

vec3 DirectionalLight::getDirn(vec3 pos) {
	return normalize(ldir);
}
float DirectionalLight::getAttenuation(float &thit, vec3 attenFac) {
	return 1;
}
vec3 DirectionalLight::getLightcol() {
	return lcol;
}
float DirectionalLight::getDis(LocalGeo local) {
	return INFINITY;
}
PointLight::PointLight(vec3 pos, vec3 col) {
	lpos = pos;
	lcol = col;
}
void PointLight::generateLightRay(LocalGeo& local, Ray* lray, vec3* lcolor) {
	vec3 dir(local.pos - lpos);
	dir = normalize(-dir);
	*lray = Ray(local.pos, dir);
	*lcolor = lcol;
}

vec3 PointLight::getDirn(vec3 pos) {
	return normalize(lpos - pos);
}
float PointLight::getAttenuation(float &thit, vec3 attenFac) {
	return 1 / (attenFac.x + attenFac.y * thit + attenFac.z * thit * thit);
}
vec3 PointLight::getLightcol() {
	return lcol;
}
float PointLight::getDis(LocalGeo local) {
	vec3 dis = (local.pos - lpos) * (local.pos - lpos);
	return sqrt(dis.x + dis.y + dis.z);
}