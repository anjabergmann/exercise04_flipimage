#include "flip.h"

int pbm_image_flip(PbmImage* image){
	char temp = ' ';
	int arraylength = (*image).width * (*image).height;

	for (int i = 0; i < arraylength / 2; i++){
		temp = (*image).data[i];
		(*image).data[i] = (*image).data[arraylength - 1 - i];
		(*image).data[arraylength - 1 -i] = temp;
	}

	return RET_PBM_OK;
}