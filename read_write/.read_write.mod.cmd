savedcmd_/home/ubuntu/ldd/read_write/read_write.mod := printf '%s\n'   read_write.o | awk '!x[$$0]++ { print("/home/ubuntu/ldd/read_write/"$$0) }' > /home/ubuntu/ldd/read_write/read_write.mod
