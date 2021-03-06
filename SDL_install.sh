#!/bin/sh

set -e

ROOTL=$PWD
OS=`uname`

if [ $OS == 'Darwin' ]
then
	if [ -d SDL2-2.0.8 ]
	then
		echo 'SDL Extracted'
	else
		echo 'SDL Extracting'
		tar -xzf SDL2-2.0.8.tar.gz
		echo 'SDL Extracted'
	fi

	if [ -d SDL2-2.0.8/build ]
	then
		echo 'SDL built'
	else
		echo 'Building SDL'
		mkdir SDL2-2.0.8/build
		cd SDL2-2.0.8/build
		CC=../build-scripts/gcc-fat.sh ../configure
		make -j4
		echo 'SDL built'
	fi

	cd $ROOTL
	mkdir -p include/SDL2
	cp SDL2-2.0.8/include/* include/SDL2/

	mkdir -p ~/lib/
	cp SDL2-2.0.8/build/build/.libs/libSDL2-2.0.0.dylib ~/lib/
	ln -F -s ~/lib/libSDL2-2.0.0.dylib ~/lib/libSDL2.dylib
else
	echo $OS
fi