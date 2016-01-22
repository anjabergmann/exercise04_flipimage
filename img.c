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
	
	//Allocate memory to save the image
	PbmImage* img = malloc(sizeof(PbmImage));
	if (img == NULL){
		*error = RET_OUT_OF_MEMORY;
		return NULL;
	}

	//Check if file is empty / doesn't exist
	if (stream == NULL){
		printf("File is empty\n");
		fclose(stream);
		*error = RET_EOF;
		return NULL;
	} 

	printf("File successfully read.\n");
	printf("Checking format (has to be P5 PGM Image).\n");


	//check if format is P5
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
	fscanf(stream, "%[#:.0-9a-zA-Z ]", comment);
	//Removes the LF-Char
	getc(stream);

	//Reads the width and height
	fscanf(stream, "%d %d", &(*img).width, &(*img).height);

	//Reads the colordepth
	int depth = 0;
	fscanf(stream, "%d", &depth);


#ifdef DEBUG
	printf("Width: %d\n", (*img).width);
	printf("Height: %d\n", (*img).height);
#endif


	//eliminates maximum intensity
	fgets((*img).data, 5, stream);


	//allocate memory for storing the image
	(*img).data = malloc((*img).width*(*img).height*sizeof(char));

	if ((*img).data == NULL){
		*error = RET_OUT_OF_MEMORY;
		return NULL;
	}


	//Reads the img-data in binary
	fread((*img).data, (*img).height * (*img).width, 1, stream);

	// //Write values from image into array
	// for (int i = 0; i < (*img).height*(*img).width; i++){
	// 		fread(&(*img).data[1], sizeof(char), 1, stream);
	// }

	return img;
}


int pbm_image_write_to_stream(PbmImage* img, FILE* targetStream){

	//write image header into file
	fprintf(targetStream, "%s\n%d %d\n255\n", (*img).type, (*img).width, (*img).height);

	//write image data into file
	fwrite((*img).data, sizeof(char), (*img).width*(*img).height, targetStream);

	return 0;
}