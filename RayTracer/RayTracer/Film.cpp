#include "Film.h"

vec3 ComputeLight(const vec3 direction, const vec3 lightcolor, const vec3 normal, const vec3 halfvec, const vec3 diffuse, const vec3 specular, const float shininess) {
	float nDotL = dot(normal, direction);
	vec3 lambert = diffuse * lightcolor * max(nDotL, 0.0f);
	float nDotH = dot(normal, halfvec);
	vec3 phong = specular * lightcolor * pow(max(nDotH, 0.0f), shininess);
	vec3 retval = lambert + phong;
	return retval;
}

vec3 Trace(Ray rayinit) {
	Ray ray = rayinit;
	int recursiveDepth = 0;
	vec3 mycolor = vec3(0, 0, 0);
	vec3 specularity(1, 1, 1);
	while (recursiveDepth < 5) {
		float thit = INFINITY;
		LocalGeo local;
		vector<Shape*>::iterator iter = shape.begin();
		bool intersection = false;
		while (iter != shape.end()) {
			if ((*iter)->intersect(ray, &thit, &local)) {
				intersection = true;
			}
			iter++;
		}
		if (intersection) {
			vector<Light*>::iterator light_iter = lights.begin();
			Ray lray;
			mycolor += vec3(local.ambient[0], local.ambient[1], local.ambient[2]);
			mycolor += vec3(local.emission[0], local.emission[1], local.emission[2]);
			vec3 lcolor;
			while (light_iter != lights.end()) {
				(*light_iter)->generateLightRay(local, &lray, &lcolor);
				iter = shape.begin();
				bool block = false;
				LocalGeo blockLocal;
				float blockThit = (*light_iter)->getDis(local);
				while (iter != shape.end()) {
					if ((*iter)->intersectPD(lray, blockThit)) {
						block = true;
						break;
					}
					iter++;
				}
				if (!block) {
					vec3 finalcolor;
					vec3 mypos = local.pos;
					vec3 eyedirn = normalize(ray.pos - mypos);
					vec3 normal = local.normal;
					vec3 direction = normalize(lray.dir);
					vec3 halfvec = normalize(direction + eyedirn);
					vec3 lightcolor = (*light_iter)->getLightcol();
					vec3 diffuse = vec3(local.diffuse[0], local.diffuse[1], local.diffuse[2]);
					vec3 specular = vec3(local.specular[0], local.specular[1], local.specular[2]);
					float shininess = local.shininess;
					vec3 disvec = local.pos - lray.pos;
					float dis = sqrt(disvec.x * disvec.x + disvec.y * disvec.y + disvec.z * disvec.z);
					float atten = (*light_iter)->getAttenuation(dis, attenuation);
					finalcolor = ComputeLight(direction, lightcolor, normal, halfvec, diffuse, specular, shininess) * specularity * atten;
					mycolor += finalcolor;
				}
				light_iter++;
			}
			if ((local.specular[0] < 0.0001f && local.specular[1] < 0.0001f && local.specular[2] < 0.0001f)) {
				break;
			}
			specularity *= vec3(local.specular[0], local.specular[1], local.specular[2]);
			ray.dir = reflect(ray.dir, local.normal);
			ray.pos = local.pos;
			recursiveDepth++;
		}
		else {
			break;
		}
	}
	if (mycolor.x > 1) {
		mycolor.x = 1;
	}
	if (mycolor.y > 1) {
		mycolor.y = 1;
	}
	if (mycolor.z > 1) {
		mycolor.z = 1;
	}
	return mycolor;
}

void Generate_thread(FIBITMAP* bitmap, Camera camera,int init_num, int thread_num) {
	for (int i = init_num; i < Width; i += thread_num) {
		cout << i << endl;
		for (int j = 0; j < Height; j++) {
			RGBQUAD color;
			vec3 mycolor;
			Ray ray = camera.GenerateRay(vec2(i, j));
			mycolor = Trace(ray);
			color.rgbRed = mycolor.x * 255;
			color.rgbGreen = mycolor.y * 255;
			color.rgbBlue = mycolor.z * 255;
			FreeImage_SetPixelColor(bitmap, i, j, &color);
		}
	}
}

void Process(FIBITMAP* bitmap, Camera camera, int thread_num) {
	//Generate_thread(bitmap, camera, 0, thread_num);
	thread **threads = new thread*[thread_num];
	for (int i = 0; i < thread_num; i++) {
		threads[i] = new thread(Generate_thread, bitmap, camera, i, thread_num);
	}

	for (int i = 0; i < thread_num; ++i) {
		threads[i]->join();
		delete threads[i];
		threads[i] = NULL;
	}
}