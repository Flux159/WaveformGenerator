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

#include <unistd.h>
#include <string.h>
#include <stdarg.h>

#define PNG_DEBUG 3
#include <png.h>

#include "waveformgenerator.h"

//typedef struct wavheader* wavheaderPointer;

wavheader* init_and_read_wavheader(FILE* fp){
	wavheader* header = malloc(sizeof(wavheader));
	
	// printf("In init_and_read_wavheader\n");
	
	//Read header here
	fread(header, sizeof(wavheader), 1, fp);
	
	/*
	* Testing what was read
	* Note that character strings will be printed oddly because of no null at 
	* the end of the string.
	*/ 
	// printf("Header chunkId: %s\n", header->chunkId);
	// printf("Header chunkSize: %d\n", header->chunkSize);
	// printf("Header format: %s\n", header->format);
	// printf("Header sampleRate: %d\n", header->sampleRate);
	// printf("Header dataSize (chunk2Size): %d\n", header->subChunk2Size);
	
	return header;
}

void dealloc_wavheader(wavheader* header){
	free(header);
}

void* init_and_read_wavdata(FILE* fp, int size){
	// printf("In read_wavdata\n");
	void* wavdata = malloc(sizeof(char)*size);
	
	fread(wavdata, sizeof(char)*size, 1, fp);
	
	return wavdata;
}

void dealloc_wavdata(void* wavdata){
	free(wavdata);
}

void create_png_image(){
	//TODO: Implement create_png_image
	// printf("In create_png_image\n");
}

int main(int argc, char *argv[]){
	
	// Usage checking
	if(argc != 3){
		printf("Usage: >> waveformgenerator <input-wav-file> <output-png-file>");
		return -1;
	}
	
	// Read from the wav file (command line argument 1)
	FILE* fp = fopen(argv[1], "rb");
	
	//Read wav file header here
	wavheader* header = init_and_read_wavheader(fp);
	
	//Read wav file data here
	void* wavdata = init_and_read_wavdata(fp, header->subChunk2Size);
	
	//Close the file pointer for the wav file input
	fclose(fp);
	
	//Create png image here with waveform
	create_png_image();
		
	dealloc_wavheader(header);
	dealloc_wavdata(wavdata);
	
	return 0;
}