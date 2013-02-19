#!/bin/sh
autoheader
touch NEWS README AUTHORS ChangeLog
touch stamp-h
aclocal
libtoolize -c -f
autoconf
automake --add-missing
./configure --prefix=$(pwd)/Product/release
make uninstall;make clean;make all;make install
