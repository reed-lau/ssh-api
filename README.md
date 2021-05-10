# ssh-api
call ssh-function via api instead of commandline tools.

#### Compile libssh
```sh
# step-1. download the source code
wget https://www.libssh.org/files/0.9/libssh-0.9.5.tar.xz

# step-2. uncompress the tarball
tar -xvf libssh-0.9.5.tar.xz

# step-3. compile the source code
cd libssh-0.9.5
mkdir build
cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=../release  -DCMAKE_BUILD_TYPE=RelWithDebInfo -DBUILD_SHARED_LIBS=OFF
make -j8
make install
```

#### Compile your application
```sh
g++ main.cc -o main -O2 -I../release/include ../release/lib/libssh.a -lcrypto -lz
```
