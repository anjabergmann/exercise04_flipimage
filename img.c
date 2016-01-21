#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "img.h"

void pbm_image_free(PbmImage* img){

} 

PbmImage* pbm_image_load_from_stream(FILE* stream, int* error){
	
	PbmImage pbmimage;

	if (stream == NULL){
		printf("File is empty\n");
		fclose(stream);
		return NULL;
	} 

	printf("File successfully read\n");

	char str[4];
	fgets(str, 4, stream); //first line of img-file



	//check if format is P5
	if (!strcmp(str, PBM_TYPE_P5)){
		printf("Unsupported format");
		*error = RET_UNSUPPORTED_FILE_FORMAT;
		return NULL;
	}

	int linelength = 255;
	char data[linelength];
	data[0] = '#';
	while (data[0] == '#'){
		fgets(data, linelength, stream);
	}

	int i = 0;
	char widthString[4];
	while (data[i] != ' ') {
		widthString[i] = data[i];
		i++;
	}

	i++;
	int j = 0;
	char heightString[4];
	while(data[i] != 0){
		heightString[j] = data[i];
		i++;
		j++;
	}


	int width = atoi(widthString);
	int height = atoi(heightString);

	printf("%d\n", width);
	printf("%d", height);


	pbmimage.width = width;
	pbmimage.height = height;

	//allocate memory for storing the image
	char* = malloc(width*height*sizeof(char));


	while(){

	}

	return NULL;
}


int pbm_image_write_to_stream(PbmImage* img, FILE* targetStream){
	return 0;
}