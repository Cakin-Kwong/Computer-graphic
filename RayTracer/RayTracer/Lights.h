#ifndef LIGHTS_HEADER
#define LIGHTS_HEADER

#include "Ray.h"
#include "LocalGeo.h"

class Light {
public:
	void virtual generateLightRay(LocalGeo& local, Ray* lray, vec3* lcolor) = 0;
	vec3 virtual getDirn(vec3 pos) = 0;
	vec3 virtual getLightcol() = 0;
	float virtual getAttenuation(float &thit, vec3 attenFac) = 0;
	float virtual getDis(LocalGeo local) = 0;
};
class DirectionalLight :public Light {
public:
	vec3 ldir;
	vec3 lcol;
	DirectionalLight(vec3 dir, vec3 color);
	void generateLightRay(LocalGeo& local, Ray* lray, vec3* lcolor);
	vec3 getDirn(vec3 pos);
	vec3 getLightcol();
	float getAttenuation(float &thit, vec3 attenFac);
	float getDis(LocalGeo local);
};
class PointLight :public Light {
public:
	vec3 lpos;
	vec3 lcol;
	PointLight(vec3 pos, vec3 col);
	void generateLightRay(LocalGeo& local, Ray* lray, vec3* lcolor);
	vec3 getDirn(vec3 pos);
	vec3 getLightcol();
	float getAttenuation(float &thit, vec3 attenFac);
	float getDis(LocalGeo local);
};

#endif