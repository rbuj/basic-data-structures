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
# Clean previos build
```
make clean
```
# Address Sanitizer build
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
