savedcmd_/home/ubuntu/ldd/hello/hello.mod := printf '%s\n'   hello.o | awk '!x[$$0]++ { print("/home/ubuntu/ldd/hello/"$$0) }' > /home/ubuntu/ldd/hello/hello.mod
