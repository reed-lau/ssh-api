all:main-ssh main-scp

main-ssh:main-ssh.cc
	g++ $< -o $@ -O2 -std=c++98 -I../release/include ../release/lib/libssh.a -lcrypto -lz
main-scp:main-scp.cc
	g++ $< -o $@ -O2 -std=c++98 -I../release/include ../release/lib/libssh.a -lcrypto -lz
