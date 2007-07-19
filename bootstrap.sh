#!/bin/sh

#
# obsolete, replaced by "autoreconf -i -W all"
#

#autoreconf -i -W all

#exit


echo "libtoolize..."
libtoolize || glibtoolize \
    || { echo "libtoolize failed"; exit 1; }
echo "aclocal..."
aclocal -I m4 \
    || { echo "aclocal failed"; exit 1; }
echo "autoheader..."
autoheader --warnings=all \
    || { echo "autoheader failed"; exit 1; }
echo "automake..."
automake --warnings=all --foreign --add-missing \
    || { echo "automake failed"; exit 1; }

echo "autoconf..."
autoconf --warnings=all \
    || { echo "autoconf failed"; exit 1; }
