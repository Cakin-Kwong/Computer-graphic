#include "Readfile.h"
vector<vec3> verts;
vector<Shape*> shape;
vector<Light*> lights;
vec3 eyeinit;
vec3 upinit;
vec3 center;
int Width, Height;
float fovy;
int maxverts;
float ambient[3];
float diffuse[3];
float specular[3];
float emission[3] = { 0, 0, 0 };
float shininess = 0;
vec3 attenuation(1, 0, 0);


void rightmultiply(const mat4 & M, stack<mat4> &transfstack)
{
	mat4 &T = transfstack.top();
	T = T * M;
}

bool readvals(stringstream &s, const int numvals, float* values)
{
	for (int i = 0; i < numvals; i++) {
		s >> values[i];
		if (s.fail()) {
			cout << "Failed reading value " << i << " will skip\n";
			return false;
		}
	}
	return true;
}
void readfile(const char * filename) {
	string str, cmd;
	ifstream in;
	in.open(filename);
	if (in.is_open()) {

		stack<mat4> transfstack;
		transfstack.push(mat4(1.0));

		getline(in, str);
		while (in) {
			if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
				stringstream s(str);
				s >> cmd;
				int i;
				float values[10];
				bool validinput;
				if (cmd == "size") {
					validinput = readvals(s, 2, values);
					if (validinput) {
						Width = (int)values[0];
						Height = (int)values[1];
					}
				}
				else if (cmd == "directional") {
					validinput = readvals(s, 6, values);
					vec3 dir = normalize(vec3(values[0], values[1], values[2]));
					vec3 col(values[3], values[4], values[5]);
					Light* light = new DirectionalLight(dir, col);
					lights.push_back(light);
				}
				else if (cmd == "point") {
					validinput = readvals(s, 6, values);
					vec3 pos(values[0], values[1], values[2]);
					vec3 col(values[3], values[4], values[5]);
					Light* light = new PointLight(pos, col);
					lights.push_back(light);
				}
				else if (cmd == "ambient") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						for (i = 0; i < 3; i++) {
							ambient[i] = values[i];
						}
					}
				}
				else if (cmd == "diffuse") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						for (i = 0; i < 3; i++) {
							diffuse[i] = values[i];
						}
					}
				}
				else if (cmd == "specular") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						for (i = 0; i < 3; i++) {
							specular[i] = values[i];
						}
					}
				}
				else if (cmd == "emission") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						for (i = 0; i < 3; i++) {
							emission[i] = values[i];
						}
					}
				}
				else if (cmd == "shininess") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						shininess = values[0];
					}
				}
				else if (cmd == "camera") {
					validinput = readvals(s, 10, values);
					eyeinit = vec3(values[0], values[1], values[2]);
					center = vec3(values[3], values[4], values[5]);
					upinit = vec3(values[6], values[7], values[8]);
					fovy = radians(values[9]);
					//fovy = values[9];
					upinit = upvector(upinit, eyeinit - center);
				}
				else if (cmd == "maxverts") {
					validinput = readvals(s, 1, values);
					maxverts = (int)values[0];
				}
				else if (cmd == "vertex") {
					validinput = readvals(s, 3, values);
					vec3 vertex(values[0], values[1], values[2]);
					verts.push_back(vertex);
				}
				else if (cmd == "tri") {
					validinput = readvals(s, 3, values);
					vector<vec3>::iterator iterB = verts.begin();
					vec3 A = pointTrans(*(iterB + (int)values[0]), transfstack.top());
					vec3 B = pointTrans(*(iterB + (int)values[1]), transfstack.top());
					vec3 C = pointTrans(*(iterB + (int)values[2]), transfstack.top());
					Shape* tri = new Triangle(A, B, C);
					//					Shape* tri = new Triangle(*(iterB + (int)values[0]), *(iterB + (int)values[1]), *(iterB + (int)values[2]));
					tri->setBRDF(ambient, diffuse, specular);
					tri->emission[0] = emission[0];
					tri->emission[1] = emission[1];
					tri->emission[2] = emission[2];
					tri->shininess = shininess;
					tri->transform = transfstack.top();
					shape.push_back(tri);
				}
				else if (cmd == "sphere") {
					validinput = readvals(s, 4, values);
					Shape* sphere = new Sphere(vec3(values[0], values[1], values[2]), values[3]);
					sphere->setBRDF(ambient, diffuse, specular);
					sphere->emission[0] = emission[0];
					sphere->emission[1] = emission[1];
					sphere->emission[2] = emission[2];
					sphere->shininess = shininess;
					sphere->transform = transfstack.top();
					shape.push_back(sphere);
				}
				else if (cmd == "translate") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						rightmultiply(Transform::translate(values[0], values[1], values[2]), transfstack);
					}
				}
				else if (cmd == "scale") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						rightmultiply(Transform::scale(values[0], values[1], values[2]), transfstack);
					}
				}
				else if (cmd == "rotate") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						glm::mat3 rotatemat = Transform::rotate(values[3], glm::normalize(vec3(values[0], values[1], values[2])));
						vec4 v1(rotatemat[0][0], rotatemat[0][1], rotatemat[0][2], 0);
						vec4 v2(rotatemat[1][0], rotatemat[1][1], rotatemat[1][2], 0);
						vec4 v3(rotatemat[2][0], rotatemat[2][1], rotatemat[2][2], 0);
						vec4 v4(0, 0, 0, 1);
						glm::mat4 transmat(v1, v2, v3, v4);
						rightmultiply(transmat, transfstack);
					}
				}
				else if (cmd == "pushTransform") {
					transfstack.push(transfstack.top());
				}
				else if (cmd == "popTransform") {
					if (transfstack.size() <= 1) {
						cerr << "Stack has no elements.  Cannot Pop\n";
					}
					else {
						transfstack.pop();
					}
				}
				else if (cmd == "attenuation") {
					validinput = readvals(s, 3, values);
					attenuation = vec3(values[0], values[1], values[2]);
				}
				else {
					cerr << "Unknown Command: " << cmd << " Skipping \n";
				}
			}
			getline(in, str);
		}
	}
	else {
		cerr << "Unable to Open Input Data File " << filename << "\n";
		throw 2;
	}
}