/*
* File waveformgenerator.c
*
* This file generates a waveform in png form from a wav audio file.
*
* Written by: Suyog Sonwalkar
* 
* 12-14-2012
*
* Usage:
*
*/

#include <stdio.h>
#include <stdlib.h>

#include "waveformgenerator.h"

//typedef struct wavheader* wavheaderPointer;

wavheader* init_and_read_wavheader(FILE* fp){
	//TODO: implement init_and_read_wavheader
	wavheader* header = malloc(sizeof(wavheader));
	
	printf("In init_and_read_wavheader\n");
	//Read header here
	
	return header;
}

void dealloc_wavheader(wavheader* header){
	free(header);
}

void read_wavdata(){
	//TODO: Implement read_wavdata
	printf("In read_wavdata\n");
}

void create_png_image(){
	//TODO: Implement create_png_image
	printf("In create_png_image\n");
}

int main(int argc, char *argv[]){
	
	// Usage checking
	if(argc != 3){
		printf("Usage: >> waveformgenerator <input-wav-file> <output-png-file>");
		return -1;
	}
	
	int i;
	char line[80];
	
	// Read from the wav file (command line argument 1)
	FILE* fp = fopen(argv[1], "r");
	
	wavheader* header = init_and_read_wavheader(fp);
	
	//Read wave file data here
	read_wavdata();
	
	//Create png image here with waveform
	create_png_image();
	
	// while(fgets(line, 80, fp) != NULL){
	// 		printf("Line: %s", line);
	// 	}
	
	fclose(fp);
	
	dealloc_wavheader(header);
	
	return 0;
}