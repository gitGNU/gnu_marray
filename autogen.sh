#! /bin/sh

# Run this script to generate all the auto-generated files needed by
# the GNU configure program.

libtoolize --automake
aclocal
automake --add-missing --gnu
autoconf

echo "Creating header files for different types..."
cd src
./generate_headers.sh
cd ..
echo "Now use ./configure"
