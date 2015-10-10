#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include "Ray.h"

class Camera {
public:
	Ray GenerateRay(vec2 sample);
};
#endif
