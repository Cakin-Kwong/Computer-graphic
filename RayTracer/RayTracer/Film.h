#ifndef FILM_HEADER
#define FILM_HEADER

#include "Headers.h"
#include "FreeImage.h"
#include "Ray.h"
#include "Lights.h"
#include "LocalGeo.h"
#include "Geometry.h"
#include "variables.h"
#include "Camera.h"
#include <thread>
#include <vector>
#include <iostream>
using namespace std;

extern vector<vec3> verts;
extern vector<Shape*> shape;
extern vector<Light*> lights;

vec3 ComputeLight(const vec3 direction, const vec3 lightcolor, const vec3 normal, const vec3 halfvec, const vec3 diffuse, const vec3 specular, const float shininess);
vec3 Trace(Ray rayinit);
void Generate_thread(FIBITMAP* bitmap, Camera camera, int init_num, int thread_num);
void Process(FIBITMAP* bitmap, Camera camera, int thread_num);

#endif