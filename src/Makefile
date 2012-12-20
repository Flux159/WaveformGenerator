UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
waveformgenerator: waveformgenerator.c waveformgenerator.h
	gcc -O2 -I/usr/local/libpng/include/libpng15 -L/usr/local/libpng/lib -lpng15 -lz -o waveformgenerator waveformgenerator.c

install:
	cp ./waveformgenerator /usr/local/bin

cleaninstall:
	rm /usr/local/bin/waveformgenerator
endif
ifeq ($(UNAME), Darwin)
waveformgenerator: waveformgenerator.c waveformgenerator.h
	gcc -O2 -I/usr/local/include/libpng15 -L/usr/local/lib -lpng15 -lz -o waveformgenerator waveformgenerator.c

install:
	cp ./waveformgenerator /usr/local/bin

cleaninstall:
	rm /usr/local/bin/waveformgenerator
endif

# waveformgenerator: waveformgenerator.c waveformgenerator.h
# 	ifeq ($(UNAME), Linux)
# 	# For Linux Installations
# 		gcc -O2 -I/usr/include/libpng12 -L/usr/lib/x86_64-linux-gnu -lpng12 -lz -o waveformgenerator waveformgenerator.c
# 	endif
# 	ifeq ($(UNAME), Darwin)
# 	# For OS X Installations
# 		gcc -O2 -I/usr/local/include/libpng15 -L/usr/local/lib -lpng15 -lz -o waveformgenerator waveformgenerator.c
# 	endif

test:
	./waveformgenerator ../test/test.wav ../test/test.png
	./waveformgenerator ../test/output.wav ../test/output.png

clean:
	rm -f waveformgenerator
