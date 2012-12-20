WaveformGenerator
=================

Creates png images of wav audio files in C

Requires libpng installed on the system. Makefile will need to be modified to point to local install of libpng (do this by checking the -I and -L flags in your local system using the following command: libpng15-config --I_opts --ldflags)

Follow this guide to update libpng on ubuntu (default version on ubuntu is 1.2): http://www.geeksww.com/tutorials/libraries/libpng/installation/installing_libpng_on_ubuntu_linux.php
