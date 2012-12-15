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

wavheader* init_and_read_wavheader(FILE* fp);
void dealloc_wavheader(wavheader* header);

void* init_and_read_wavdata(FILE* fp, int size);
void dealloc_wavdata(void* wavdata);

