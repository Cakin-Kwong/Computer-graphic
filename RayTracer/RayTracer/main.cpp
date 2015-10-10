#include "Readfile.h"
#include "Film.h"
#include "Camera.h"
#include "variables.h"
int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "ERROR: NO INPUT FILE\n";
		exit(1);
	}
	readfile(argv[1]);
	Camera camera;
	FIBITMAP* bitmap = FreeImage_Allocate(Width, Height, BPP);
	Process(bitmap, camera, 8);
	FreeImage_Save(FIF_PNG, bitmap, "filename.png", 0);
	return 0;
}