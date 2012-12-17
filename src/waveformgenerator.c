/*
* File waveformgenerator.c
*
* This file generates a waveform in png form from a wav audio file.
*
* Written by: Suyog Sonwalkar
* 
* 12-14-2012
*
* Usage: >> waveformgenerator <input-wav-file> <output-png-file>
*
*/

//File input and output & memory allocation (malloc and free)
#include <stdio.h>
#include <stdlib.h>

//Utility classes for argument parsing and string manipulation
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

//libpng for creating png images
#define PNG_DEBUG 3
#include "/usr/local/include/libpng15/png.h"

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
	printf("Header chunkId: %s\n", header->chunkId);
	printf("Header chunkSize: %d\n", header->chunkSize);
	printf("Header format: %s\n", header->format);
	printf("Header sampleRate: %d\n", header->sampleRate);
	printf("Header dataSize (chunk2Size): %d\n", header->subChunk2Size);
	
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

short convert(short val){
	// short rightbyte = val & 0xff;
	// short leftbyte = (val >> 8) & 0xff;
	// return ((rightbyte << 8) | leftbyte);
	
	// return (((val >> 8) & 0xff) | ((val << 8)));
	
	return val;
}

png_bytep* init_waveform_and_process_wavdata(png_structp png_ptr, int width, int height, png_byte bitDepth, png_byte colorType, void* wavData, wavheader* wavHeader){

	int pixel_size = 4;
	int i;
	png_bytep* row_pointers = png_malloc(png_ptr, height*sizeof(png_bytep));
	for (i=0; i<height; i++){
		row_pointers[i]=png_malloc(png_ptr, width*pixel_size);
	}
	
	//Have access to the wav file data, the rows and pixels of the png image
	//Need to calculate the waveform image from the wavData and populate row_pointers appropriately
	
	short channels = wavHeader->numChannels;
	if(wavHeader->bitsPerSample == 8){
		char* audioData = (char*)wavData;
		
		printf("Char AudioData:\n");
		printf("%d, %d, %d, %d\n", (int)audioData[0], (int)audioData[1], (int)audioData[2], (int)audioData[3]);
		
	}
	else if(wavHeader->bitsPerSample == 16){
		short* audioData = (short*)wavData;
		
		printf("Number of channels: %d\n", (int)channels);
		printf("Size of AudioData: %d\n", (int)wavHeader->subChunk2Size);
		printf("Short AudioData:\n");
		printf("%d, %d, %d, %d\n", (int)audioData[10000], (int)audioData[10001], (int)audioData[2], (int)audioData[3]);
		
		//The total number of audio samples (taking into account short values & the number of channels)
		int sizeOfAudioIndexData = ((wavHeader->chunkSize))/(2);
		//The frame size is the total number of samples within a single frame of the png image
		int frameSize = sizeOfAudioIndexData / (width);
		//The total frames is the number of frames (it should be equal to the width)
		//int totalFrames = sizeOfAudioIndexData / frameSize;
		
		//Framepeaks stores the peaks in each frame
		short framePeaks[width];
		// int frameRMS[totalFrames];
		float framePeaksDoubles[width];
		int sampleIndex, frameIndex;
		
		printf("Size of AudioData: %d\n", sizeOfAudioIndexData);
		printf("TotalFrames: %d\n", width);
		printf("Frame Size: %d\n", frameSize);
		
		for(frameIndex = 0; frameIndex < width; frameIndex++){
			framePeaks[frameIndex] = 0;
		}
		// int j,k;
		int temp;
		
		//I believe that the issue is when I have 2 channels, I'm doing something incorrect where my image ends up only really having like 1/4 of the samples that it needs to get the full image...
		for(sampleIndex = 0; sampleIndex < sizeOfAudioIndexData; sampleIndex++){
			//Peaks
			
			if((sampleIndex/frameSize) < width){
				if(framePeaks[(sampleIndex/(frameSize))] < (short)abs((int)audioData[sampleIndex])){
					//printf(".");
					framePeaks[(sampleIndex/(frameSize))] = (short)abs((int)audioData[sampleIndex]);
				}
			}
			
			// if((sampleIndex/(frameSize)) < width){
			// 				if(framePeaks[(sampleIndex/(frameSize))] < (short)abs((int)audioData[sampleIndex*channels])){
			// 					//printf(".");
			// 					framePeaks[(sampleIndex/(frameSize))] = (short)abs((int)audioData[sampleIndex*channels]);
			// 				}
			// 				if(channels == 2){
			// 					if(framePeaks[(sampleIndex/(frameSize))] < (short)abs((int)audioData[sampleIndex*channels+1])){
			// 						//printf("/");
			// 						framePeaks[(sampleIndex/(frameSize))] = (short)abs((int)audioData[sampleIndex*channels+1]);
			// 					}
			// 				}
			// 			}
			// 			if(sampleIndex % frameSize == 0){
			// 				printf("SampleIndex: %d", sampleIndex);
			// 			}
			
			
			//RMS
			// frameRMS[(sampleIndex)/frameSize] += pow((abs((int)audioData[sampleIndex*channels])), 2);
			
			//framePeaks[(sampleIndex)/frameSize] += 

			// if((sampleIndex % 1000000) == 0){
			// 				printf("Sample index: %d", sampleIndex);
			// 			}
			// audioData[sampleIndex*channels]
		}
		
		printf("FramePeaksDoubles: \n");
		for(frameIndex = 0; frameIndex < width; frameIndex++){
			// framePeaks[frameIndex] = (short)sqrt(frameRMS[(sampleIndex)/frameSize]);
			// printf("%d, ", framePeaks[frameIndex]);
			
			int scaleFactor = 32768;
			// scaleFactor = 65536;
			
			framePeaksDoubles[frameIndex] = ((float)framePeaks[frameIndex])/scaleFactor;
			//printf("%f, ", (framePeaksDoubles[frameIndex]*(height/2)));
			framePeaks[frameIndex] = (short)(framePeaksDoubles[frameIndex]*(height/2));
			//printf("%d, ", (int)framePeaks[frameIndex]);
		}
		printf("\n");
		
		//Now set each image column based on the framePeak (ignoring the last few)
		for(frameIndex = 0; frameIndex < width; frameIndex++){
			short currentPeak = framePeaks[frameIndex];
			// draw_line(row_pointers, currentPeak, height);
			int minRow = (height/2)-currentPeak;
			int maxRow = (height/2)+currentPeak;
			int x;
			for(x = 0; x < height; x++){
				png_byte* row = row_pointers[x];
				png_byte* ptr = &(row[frameIndex*4]);
				ptr[0] = 255;
				ptr[1] = 255;
				ptr[2] = 255;
				ptr[3] = 255;
			}
			
			if(maxRow == minRow){
				maxRow = maxRow+1;
			}
			for(x = minRow; x < maxRow; x++){
				png_byte* row = row_pointers[x];
				png_byte* ptr = &(row[frameIndex*4]);
				ptr[0] = 0;
				ptr[1] = 0;
				ptr[2] = 255;
				ptr[3] = 255;
			}
		}
		
	}
	
	
	return row_pointers;
}

float audio_peak(void* wavData, int frameLeft, int frameRight){
	int i;
	float peak = 0;
	for(i = frameLeft; i < frameRight; i++){
		//abs(wavData[i])
	}
}

void dealloc_waveformdata(png_bytep* row_pointers, int height){
	// free(waveformdata);
	int i;
	for(i = 0; i < height; i++){
		free(row_pointers[i]);
	}
	free(row_pointers);
}

/*
* Read this for more knowledge about writing PNG files:
* http://www.libpng.org/pub/png/libpng-1.2.5-manual.html#section-4.1
*/
int createPNGImage(FILE* fp, int width, int height, png_byte bitDepth, png_byte colorType, void* wavData, wavheader* wavHeader){
	//TODO: Implement create_png_image
	printf("In create_png_image\n");
	
	/*
	* Initialize libpng
	*/
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, (png_voidp)NULL, NULL, NULL);
	if(!png_ptr){
		printf("Error creating png image: Could not create png_ptr.\n");
		return -1;
	}
	
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if(!info_ptr){
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		printf("Error creating png image: Could not create info_ptr.\n");
		return -1;
	}
	
	if(setjmp(png_jmpbuf(png_ptr))){
		printf("Error creating png image: Error during init_io.\n");
		return -1;
	}
	
	png_init_io(png_ptr, fp);
	
	/*
	* Write png file header
	*/
	if(setjmp(png_jmpbuf(png_ptr))){
		printf("Error creating png image: Error during write header.\n");
		return -1;
	}
	
	png_set_IHDR(png_ptr, info_ptr, width, height, bitDepth, colorType, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	
	png_write_info(png_ptr, info_ptr);
			
	/*
	* Populate waveform data
	*/
	
	png_bytep* waveformData = init_waveform_and_process_wavdata(png_ptr, width, height, bitDepth, colorType, wavData, wavHeader);

	/*
	* Write png file data
	*/
	if(setjmp(png_jmpbuf(png_ptr))){
		printf("Error creating png image: Error during write data.\n");
		return -1;
	}
	
	// Can't currently write image because I don't have row_pointers or waveform data correctly set up
	// Plus row_pointers needs to be of size 4*png_byte*width*height (if I use 8 as bit depth)
	png_write_image(png_ptr, waveformData);
	
	/*
	* End png file write
	*/
	if(setjmp(png_jmpbuf(png_ptr))){
		printf("Error creating png image: Error during end of write.\n");
		return -1;
	}
	
	png_write_end(png_ptr, NULL);
	
	/*
	* Cleanup
	*/
	dealloc_waveformdata(waveformData, height);
	
}

int main(int argc, char *argv[]){
	
	// Usage checking
	if(argc != 3){
		printf("Usage: >> waveformgenerator <input-wav-file> <output-png-file>");
		return -1;
	}
	
	// Read from the wav file (command line argument 1)
	FILE* wavFile = fopen(argv[1], "rb");
	if(!wavFile){
		printf("Error opening file: %s", argv[1]);
		return -1;
	}
	
	//Read wav file header here
	wavheader* wavHeader = init_and_read_wavheader(wavFile);
	
	//Read wav file data here
	void* wavData = init_and_read_wavdata(wavFile, (wavHeader->chunkSize)-44);
	
	//Close the file pointer for the wav file input
	fclose(wavFile);
		
	/*
	* Should get these variables from command line (have defaults as well)
	*/
	int width = 1800;
	int height = 280;
	png_byte colorType = PNG_COLOR_TYPE_RGB_ALPHA;
	png_byte bitDepth = 8;
	
	/*
	* Open pngFile
	*/
	FILE* pngFile = fopen(argv[2], "wb");
	if(!pngFile){
		printf("Error opening file: %s", argv[2]);
		
		//Free memory
		dealloc_wavheader(wavHeader);
		dealloc_wavdata(wavData);
		
		return -1;
	}
	
	//Create png image here with waveform
	createPNGImage(pngFile, width, height, bitDepth, colorType, wavData, wavHeader);
	
	//Close pngFile
	fclose(pngFile);
		
	//Free memory
	dealloc_wavheader(wavHeader);
	dealloc_wavdata(wavData);
	
	return 0;
}