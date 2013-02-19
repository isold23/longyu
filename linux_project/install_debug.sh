#!/bin/sh
autoheader
touch NEWS README AUTHORS ChangeLog
touch stamp-h
aclocal
libtoolize -c -f
autoconf
automake --add-missing
./configure --enable-debug --prefix=$(pwd)/Product/debug
make uninstall;make clean;make all;make install
