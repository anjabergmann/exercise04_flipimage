#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "img.h"
#include "flip.h"

int main(int argc, char const *argv[])
{

	if (argc != 3){
		fprintf(stderr, "You haven't inserted an input and output file!\n");
		return -1;
	}

	//load file
	FILE *f;
	f = fopen(argv[1], "r");

	//output file
	FILE *out;
	out = fopen(argv[2], "w");

	PbmImage* pbmimage;
	int error = RET_PBM_OK;
	//read image data from file
	pbmimage = pbm_image_load_from_stream(f, &error);

	//Flip image
	error = pbm_image_flip(pbmimage);

	//write image data to file
	error = pbm_image_write_to_stream(pbmimage, out);

	return 0;
}