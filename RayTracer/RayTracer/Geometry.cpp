#include "Geometry.h"
#include "Transform.h"

const float pi = 3.14159265f;
const float t_min = 0.0001f;

void Shape::setBRDF(float* ka, float* kd, float* ks) {
	for (int i = 0; i < 3; i++) {
		ambient[i] = ka[i];
		diffuse[i] = kd[i];
		specular[i] = ks[i];
	}
}

Sphere::Sphere(vec3 center, float Radius) {
	pos = center;
	radius = Radius;
}
bool Sphere::intersect(Ray& ray, float* thit, LocalGeo* local) {
	mat4 inversemat = inverse(transform);
	vec3 mypos = pointTrans(ray.pos, inversemat);
	vec3 mydir = vecTrans(ray.dir, inversemat);
	float a = dot(mydir, mydir);
	float b = 2 * dot(mydir, mypos - pos);
	float c = dot(mypos - pos, mypos - pos) - radius * radius;
	float re = b * b - 4 * a * c;
	if (b * b - 4 * a * c < 0) {
		return false;
	}
	else if (b * b - 4 * a * c == 0) {
		if (*thit > -b / (2 * a)) {
			if (-b / (2 * a) < t_min) {
				return false;
			}
			*thit = -b / (2 * a);
			vec3 hitpos = pointTrans(mypos + mydir * (*thit), transform);
			vec3 hitnorm = normalize(vecTrans(mypos + mydir * (*thit) - pos, transpose(inversemat)));
			local->set(hitpos, hitnorm);
			//local->set(ray.pos + ray.dir * (*thit), pos - ray.pos + ray.dir * (*thit));
			for (int i = 0; i < 3; i++) {
				local->ambient[i] = ambient[i];
				local->diffuse[i] = diffuse[i];
				local->specular[i] = specular[i];
				local->emission[i] = emission[i];
			}
			local->shininess = shininess;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		float rest1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
		float rest2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		if (rest1 < 0) {
			if (rest2 < *thit) {
				if (rest2 < t_min) {
					return false;
				}
				*thit = rest2;
				vec3 hitpos = pointTrans(mypos + mydir * (*thit), transform);
				vec3 hitnorm = normalize(vecTrans(mypos + mydir * (*thit) - pos, transpose(inversemat)));
				local->set(hitpos, hitnorm);
				//local->set(ray.pos + ray.dir * (*thit), pos - ray.pos + ray.dir * (*thit));
				for (int i = 0; i < 3; i++) {
					local->ambient[i] = ambient[i];
					local->diffuse[i] = diffuse[i];
					local->specular[i] = specular[i];
					local->emission[i] = emission[i];
				}
				local->shininess = shininess;
				return true;
			}
			else {
				return false;
			}
		}
		else if (rest2 < t_min) {
			if (rest1 < *thit) {
				if (rest1 < t_min) {
					return false;
				}
				*thit = rest1;
				vec3 hitpos = pointTrans(mypos + mydir * (*thit), transform);
				vec3 hitnorm = normalize(vecTrans(mypos + mydir * (*thit) - pos, transpose(inversemat)));
				local->set(hitpos, hitnorm);
				//local->set(ray.pos + ray.dir * (*thit), pos - ray.pos + ray.dir * (*thit));
				for (int i = 0; i < 3; i++) {
					local->ambient[i] = ambient[i];
					local->diffuse[i] = diffuse[i];
					local->specular[i] = specular[i];
					local->emission[i] = emission[i];
				}
				local->shininess = shininess;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (rest1 > rest2) {
				if (rest2 < *thit) {
					*thit = rest2;
					vec3 hitpos = pointTrans(mypos + mydir * (*thit), transform);
					vec3 hitnorm = normalize(vecTrans(mypos + mydir * (*thit) - pos, transpose(inversemat)));
					local->set(hitpos, hitnorm);
					//local->set(ray.pos + ray.dir * (*thit), pos - ray.pos + ray.dir * (*thit));
					for (int i = 0; i < 3; i++) {
						local->ambient[i] = ambient[i];
						local->diffuse[i] = diffuse[i];
						local->specular[i] = specular[i];
						local->emission[i] = emission[i];
					}
					local->shininess = shininess;
					return true;
				}
				else {
					return false;
				}
			}
			else {
				if (rest1 < *thit) {
					*thit = rest1;
					vec3 hitpos = pointTrans(mypos + mydir * (*thit), transform);
					vec3 hitnorm = normalize(vecTrans(mypos + mydir * (*thit) - pos, transpose(inversemat)));
					local->set(hitpos, hitnorm);
					//local->set(ray.pos + ray.dir * (*thit), pos - ray.pos + ray.dir * (*thit));
					for (int i = 0; i < 3; i++) {
						local->ambient[i] = ambient[i];
						local->diffuse[i] = diffuse[i];
						local->specular[i] = specular[i];
						local->emission[i] = emission[i];
					}
					local->shininess = shininess;
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
}
bool Sphere::intersectPD(Ray& ray, float tmax) {
	mat4 inversemat = inverse(transform);
	vec3 mypos = pointTrans(ray.pos, inversemat);
	vec3 mydir = vecTrans(ray.dir, inversemat);
	//float a = dot(ray.dir, ray.dir);
	//float b = 2 * dot(ray.dir, ray.pos - pos);
	//float c = dot(ray.pos - pos, ray.pos - pos) - radius * radius;
	/*vec3 dist = pos - ray.pos;
	float tmax = sqrt(dist.x * dist.x + dist.y * dist.y + dist.z * dist.z);*/
	float a = dot(mydir, mydir);
	float b = 2 * dot(mydir, mypos - pos);
	float c = dot(mypos - pos, mypos - pos) - radius * radius;
	float re = b * b - 4 * a * c;
	if (b * b - 4 * a * c < 0) {
		return false;
	}
	else if (b * b - 4 * a * c == 0) {
		if (-b / (2 * a) < t_min || -b / (2 * a) > tmax) {
			return false;
		}
		else return true;
	}
	else {
		float rest1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
		float rest2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		if (rest1 >= t_min && rest1 <= tmax) {
			return true;
		}
		else if ((rest2 >= t_min && rest2 <= tmax)) {
			return true;
		}
		else {
			return false;
		}
	}
}

Triangle::Triangle(vec3 A, vec3 B, vec3 C) {
	Apos = A;
	Bpos = B;
	Cpos = C;
	normal = normalize(cross((Cpos - Apos), (Bpos - Apos)));
}
bool Triangle::intersect(Ray& ray, float* thit, LocalGeo* local) {
	if (dot(ray.dir, normal) == 0) {
		return false;
	}
	else {
		float t = (dot(Apos, normal) - dot(ray.pos, normal)) / dot(ray.dir, normal);
		if (t < t_min || t > *thit) {
			return false;
		}
		else {
			float beta = 0, gama = 0;
			vec3 Point = ray.pos + t * ray.dir;
			solve(Point, &beta, &gama);
			if (beta >= 0 && beta <= 1 && gama >= 0 && gama <= 1 && beta + gama <= 1) {
				*thit = (dot(Apos, normal) - dot(ray.pos, normal)) / dot(ray.dir, normal);
				if (dot(ray.dir, normal) > 0) {
					local->set(ray.pos + ray.dir * (*thit), -normal);
				}
				else {
					local->set(ray.pos + ray.dir * (*thit), normal);
				}
				for (int i = 0; i < 3; i++) {
					local->ambient[i] = ambient[i];
					local->diffuse[i] = diffuse[i];
					local->specular[i] = specular[i];
					local->emission[i] = emission[i];
				}
				local->shininess = shininess;
				return true;
			}
			else {
				return false;
			}
		}
	}
}
bool Triangle::intersectPD(Ray& ray, float tmax) {
	if (dot(ray.dir, normal) == 0) {
		return false;
	}
	else {
		float t = (dot(Apos, normal) - dot(ray.pos, normal)) / dot(ray.dir, normal);
		if (t < t_min || t > tmax) {
			return false;
		}
		float beta = 0, gama = 0;
		vec3 Point = ray.pos + t * ray.dir;
		solve(Point, &beta, &gama);
		if (beta >= 0 && beta <= 1 && gama >= 0 && gama <= 1 && beta + gama <= 1) {
			return true;
		}
		else {
			return false;
		}
	}
}
void Triangle::solve(vec3 Point, float* beta, float* gama) {
	vec3 w = Point - Apos;
	vec3 u = Bpos - Apos;
	vec3 v = Cpos - Apos;
	*beta = (dot(u, v) * dot(w, v) - dot(v, v) * dot(w, u)) / (dot(u, v) * dot(u, v) - dot(u, u) * dot(v, v));
	*gama = (dot(u, v) * dot(w, u) - dot(u, u) * dot(w, v)) / (dot(u, v) * dot(u, v) - dot(u, u) * dot(v, v));
}