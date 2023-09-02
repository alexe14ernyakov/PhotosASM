#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define	STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#ifdef asm
void process(unsigned char* img2, unsigned char* img1, int width, int height, int channels);
#else
void c_process(unsigned char* img2, unsigned char* img1, int width, int height, int channels){
	printf("%d\n", width * height * channels);
	for(size_t i = 0; i < width * height * channels; i+=channels){
		//printf("%uc %uc %uc\n", img1[i], img1[i+1], img1[i+2]);
		unsigned char a = img1[i];
		//unsigned char b = img1[i+1];
		//unsigned char c = img1[i+2];
		if(channels == 4){
			img2[i+3] = img1[i+3];
		}
		unsigned char g = a;
		memset(img2+i, g, 3);
	}	
}
#endif

int main(int argc, char** argv){
	clock_t begin = clock();
	
	if(argc < 2){
		printf("There are no all arguments\n");
		return 1;
	}
	char* filename1 = argv[1];
	char* filename2 = argv[2];

	int width, height, channels;
	unsigned char* image = stbi_load(filename1, &width, &height, &channels, 0);
	if(image == NULL){
		printf("Error in loading the image\n");
		return 1;
	}

	printf("Loaded image with a width of %dpx and height of %dpx and %d channels\n", width, height, channels);

	#ifndef asm
	c_process(image, image, width, height, channels);	
	#else
	process(image, image, width, height, channels);
	#endif
	
	stbi_write_jpg(filename2, width, height, channels, image, 0);

	clock_t end = clock();
	double runtime = (double)(end - begin)/ CLOCKS_PER_SEC;
	printf("Process took %lf seconds ", runtime);
	#ifdef asm
	printf("with extern function in ASM");
	#endif
		
	return 0;	
}
