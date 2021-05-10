# ssh-api
call ssh-function via api instead of commandline tools.

#### Method-1: Compile libssh (with default openssl)
```sh
# step-1. download the source code
wget -nc https://www.libssh.org/files/0.9/libssh-0.9.5.tar.xz

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

#### Method-2: Compile libssh with mbedtls
```sh
wget -nc https://github.com/ARMmbed/mbedtls/archive/refs/tags/v2.26.0.tar.gz -O mbedtls.tar.gz
tar xvzf mbedtls.tar.gz

cd mbedtls-2.26.0
mkdir build
cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=../release
make install -j4
cd ../
cd ../
```

```sh
# step-1. download the source code
wget -nc https://www.libssh.org/files/0.9/libssh-0.9.5.tar.xz

# step-2. uncompress the tarball
tar -xvf libssh-0.9.5.tar.xz

# step-3. compile the source code
cd libssh-0.9.5
mkdir build
cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=../release -DWITH_MBEDTLS=ON -DMBEDTLS_ROOT_DIR=`pwd`/../../mbedtls-2.26.0/release
cmake ../ -DCMAKE_INSTALL_PREFIX=../release  -DCMAKE_BUILD_TYPE=RelWithDebInfo -DBUILD_SHARED_LIBS=OFF
make -j8
make install
```


#### Compile your application
```sh
g++ main.cc -o main -O2 -I../release/include ../release/lib/libssh.a -lcrypto -lz
```
