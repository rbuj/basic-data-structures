#!/bin/sh
aclocal
autoconf
automake --add-missing
autoreconf -f -i -v
