/*
* Include file for waveformgenerator.c
*
* Written by: Suyog Sonwalkar
*
* 12-14-2012
*/

/*
* Format of wave file header obtained from here: https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
*/
typedef struct wavheader{
	char chunkId[4];
	int chunkSize;
	char format[4];
	char subChunk1Id[4];
	int subChunk1Size;
	short audioFormat;
	short numChannels;
	int sampleRate;
	int byteRate;
	short blockAlign;
	short bitsPerSample;
	char subChunk2Id[4];
	int subChunk2Size;
} wavheader;

/*
* Functions to read wavheader and deallocate memory once completed
*/
wavheader* init_and_read_wavheader(FILE* fp);
void dealloc_wavheader(wavheader* header);

/*
* Functions to read wavdata and deallocate memory once completed
*/
void* init_and_read_wavdata(FILE* fp, int size);
void dealloc_wavdata(void* wavdata);

/*
* Format of png file
* Information obtained here:
*		http://en.wikipedia.org/wiki/Portable_Network_Graphics
*		http://www.libpng.org/pub/png/spec/1.2/PNG-Structure.html
*		http://www.libpng.org/pub/png/spec/1.2/PNG-CRCAppendix.html
* Using libpng to create png files since its been tested and works (libpng uses zlib)
*/
// #define PNG_HEADER 0x89504E470D0A1A0A
