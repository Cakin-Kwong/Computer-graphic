#include "LocalGeo.h"

void LocalGeo::setPos(vec3 position) {
	pos = position;
}
void LocalGeo::setnormal(vec3 norm) {
	normal = normalize(norm);
}
void LocalGeo::set(vec3 position, vec3 norm) {
	pos = position;
	normal = normalize(norm);
}