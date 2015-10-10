#ifndef READFILE_HEADER
#define READFILE_HEADER

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include "Geometry.h"
#include "Transform.h"
#include "Lights.h"
using namespace std;

bool readvals(stringstream &s, const int numvals, float * values);
void readfile(const char * filename);

#endif
