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
