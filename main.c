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
	if (pbmimage == NULL){
		return error;
	}

	printf("Type: %s\n", (*pbmimage).type);
	printf("Height: %d\n", (*pbmimage).height);
	printf("Width: %d\n", (*pbmimage).width);
	printf("Data: %s\n", (*pbmimage).data);

	//Flip image
	error = pbm_image_flip(pbmimage);
	if(error != 0){
		return error;
	}

	//write image data to file
	error = pbm_image_write_to_stream(pbmimage, out);
	if(error != 0){
		return error;
	}

	//free allocated memory
	pbm_image_free(pbmimage);

	return RET_PBM_OK;
}