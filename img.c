#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "img.h"

void pbm_image_free(PbmImage* img){
	if ((*img).data != NULL){
		free((*img).data);
	}
	if(img != NULL){
		free(img);
	} 
}

PbmImage* pbm_image_load_from_stream(FILE* stream, int* error){

	//Checks if file is empty / doesn't exist
	if (stream == NULL){
		printf("File is empty\n");
		fclose(stream);
		*error = RET_EOF;
		return NULL;
	} 

	printf("File successfully read.\n");


	//Allocates memory to save the image
	PbmImage* img = malloc(sizeof(PbmImage));
	if (img == NULL){
		*error = RET_OUT_OF_MEMORY;
		return NULL;
	}


	//checks if format is P5
	printf("Checking format (has to be P5 PGM Image).\n");
	fscanf(stream, "%[0-9a-zA-Z]", (*img).type);

#ifdef DEBUG
	printf("[DEBUG] Image type: %s\n", (*img).type);
#endif

	if (strcmp((*img).type, PBM_TYPE_P5) != 0){
		printf("Unsupported format.\n");
		*error = RET_INVALID_FORMAT;
		return NULL;
	} else {
		printf("Format okay.\n");
	}



	//Removes LF-Char
	getc(stream);

	//Reads the Comment
	char comment [80];
	//do {
		fscanf(stream, "%[#:.0-9a-zA-Z ]", comment);
		//Removes the LF-Char
		getc(stream);
	//} while (lineStartsWith#)


	//Reads the width and height
	fscanf(stream, "%d %d", &(*img).width, &(*img).height);
	//Removes LF-Char
	getc(stream);

#ifdef DEBUG
	printf("Width: %d\n", (*img).width);
	printf("Height: %d\n", (*img).height);
#endif


	//Reads the colordepth
	int depth = 0;
	fscanf(stream, "%d", &depth);



	//calculates size of image data / array
	int size = (*img).width * (*img).height + 1;

	//allocate memory for storing the image
	(*img).data = malloc(size *sizeof(char));

	//checks if allocating storage succeded
	if ((*img).data == NULL){
		*error = RET_OUT_OF_MEMORY;
		return NULL;
	}

	//Removes LF-Char
	getc(stream);
	//Reads the img-data in binary
	fread((*img).data, size, 1, stream);

	return img;
}


int pbm_image_write_to_stream(PbmImage* img, FILE* targetStream){

	//write image header into file
	fprintf(targetStream, "%s\n%d %d\n255\n", (*img).type, (*img).width, (*img).height);

	//write image data into file
	fwrite((*img).data, sizeof(char), (*img).width*(*img).height, targetStream);

	return 0;
}