obj-m += hello.o
# all object files that are behind this obj-m variable will be built as kernel modules
# compilation from hello.c to hello.o is done automatically by the makefile of the linux kernel headers

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean