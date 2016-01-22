#include "flip.h"

int pbm_image_flip(PbmImage* image){
	
	printf("\n________________________________________\n\n");
	printf("\n Rotating Image ...\n");
	printf("\n________________________________________\n\n");

	char temp = ' ';
	int arraylength = (*image).width * (*image).height + 1;


	for (int i = 0; i < arraylength / 2; i++){
		temp = (*image).data[i];
		(*image).data[i] = (*image).data[arraylength -2 -i];
		(*image).data[arraylength -2 - i] = temp;
#ifdef DEBUG
		if (i < 50){ //not really usefull with large arrays
			printf("index: %d old value: %c new value: %c\n", i, (*image).data[i], (*image).data[arraylength - 1 - i]);
			printf("index: %d old value: %c new value: %c\n", arraylength-1-i, (*image).data[arraylength-1-i], (*image).data[i]);
		}
#endif
	}

	return RET_PBM_OK;
}