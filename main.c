#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "img.h"

int main(int argc, char const *argv[])
{

	if (argc != 3){
		fprintf(stderr, "You haven't inserted an input and output file!\n");
		return -1;
	}

	//load file
	FILE *f;
	f = fopen(argv[1], "r");

	PbmImage* pbmimage;
	int error = RET_PBM_OK;
	pbmimage = pbm_image_load_from_stream(f, &error);

	return 0;
}