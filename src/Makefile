waveformgenerator: waveformgenerator.c waveformgenerator.h
	gcc -O2 -I/usr/local/include/libpng15 -L/usr/local/lib -lpng15 -lz -o waveformgenerator waveformgenerator.c

test:
	./waveformgenerator ../test/test.wav ../test/test.png
	./waveformgenerator ../test/output.wav ../test/output.png

clean:
	rm -f waveformgenerator
