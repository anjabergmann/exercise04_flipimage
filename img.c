#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "img.h"

void pbm_image_free(PbmImage* img){
	free((*img).data);
	free(img);
} 

PbmImage* pbm_image_load_from_stream(FILE* stream, int* error){
	
	PbmImage* img = malloc(sizeof(PbmImage));

	if (stream == NULL){
		printf("File is empty\n");
		fclose(stream);
		return NULL;
	} 

	printf("File successfully read\n");


	fgets((*img).type, 4, stream); //first line of img-file

	//check if format is P5
	if (!strcmp((*img).type, PBM_TYPE_P5)){
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


	(*img).width = width;
	(*img).height = height;


	//eliminate maximum intensity
	fgets(data, 5, stream);


	//allocate memory for storing the image
	(*img).data = malloc(width*height*sizeof(char));


	//Write values from image into array
	char temp = ' ';
	for (i = 0; i < height*width; i++){
			fread(&temp, sizeof(char), 1, stream);
			(*img).data[i] = temp;
#ifdef DEBUG
			printf("i: %d temp: %c\n", i, temp);
#endif
	}

	return img;
}


int pbm_image_write_to_stream(PbmImage* img, FILE* targetStream){

	//write image header into file
	fprintf(targetStream, "%s%d %d\n255\n", (*img).type, (*img).width, (*img).height);

	//write image data into file
	fwrite((*img).data, sizeof(char), (*img).width*(*img).height, targetStream);

	return 0;
}