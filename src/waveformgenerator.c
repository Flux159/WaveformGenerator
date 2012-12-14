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
	while(fgets(line, 80, fp) != NULL){
		printf("Line: %s", line);
	}
	fclose(fp);
	
	return 0;
}