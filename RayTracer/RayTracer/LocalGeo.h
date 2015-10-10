#ifndef LOCALGEO_HEADER
#define LOCALGEO_HEADER

#include "Headers.h"

class LocalGeo {
public:
	vec3 pos;
	vec3 normal;
	float ambient[3];
	float diffuse[3];
	float specular[3];
	float emission[3];
	float shininess;
	void setPos(vec3 position);
	void setnormal(vec3 norm);
	void set(vec3 position, vec3 norm);
};

#endif
