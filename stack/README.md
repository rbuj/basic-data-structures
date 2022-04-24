# Install buildeps on Fedora
```
sudo dnf install gcc make autoconf automake pkg-config check-devel libasan
```
# Regular build
```
./autogen.sh
./configure
make
```
# Run unit tests
```
make check
```
# Run sample code
```
./src/test
```
# Clean previous build
```
make clean
```
# Address sanitizer build
```
./autogen.sh
CC=clang CFLAGS=-O0 ./configure --enable-sanitize
make
```
# Profiler build
```
./autogen.sh
./configure --enable-profile
make
```
