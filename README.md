# LDD
Linux Device Drivers

sudo dmesg -W //to keep watching logs -w is also there
sudo dmesg | tail //last 5 lines
sudo dmesg | tail -n 1 //last 1 line

sudo insmod hello.ko //to insert

sudo rmmod hello.ko //to remove

ubuntu@primary:~/ldd/better_hello$ modinfo better_hello.ko
filename:       /home/ubuntu/ldd/better_hello/better_hello.ko
description:    A simple hello world Linux Kernel Module
author:         Kalpit Rathod <99kalpitrathod@gmail.com>
license:        GPL
srcversion:     B2F1CFC469EF0E468891D12
depends:        
retpoline:      Y
name:           better_hello
vermagic:       6.8.0-106-generic SMP preempt mod_unload modversions 

ubuntu@primary:~/ldd/better_hello$ lsmod
Module                  Size  Used by
better_hello           12288  0
isofs                  61440  0
binfmt_misc            24576  1
nls_iso8859_1          12288  1
joydev                 32768  0

major and minor device number
cat /proc/devices //which device number belongs to which driver
ls -lh /dev/<device>

sudo hexdump /dev/<device> | head
//to see dump to bytes

sudo mknod mymmc b 179 0 //add device manually

first we have to allocate a device number
device number consist of a major device number and a minor device number
every major device number can have 256 minor device numbers
we have to register the device number
we have to create character device and bind this character device to the device number

[ 4061.753480] cdev_kalpit - Major Device Number: 241

//create device file and link /dev/hello0 its character device with 241
ubuntu@primary:~/ldd/cdev$ sudo mknod /dev/hello0 c 241 0
// to delete it do sudo rm /dev/hello0

//bootlin.com browse the sources of the linux kernel
fs.h has the file operations like read write function pointers
we can overload only we we want

ubuntu@primary:~/ldd/cdev$ sudo cat /dev/hello0

ubuntu@primary:~/ldd/better_hello$ sudo dmesg -W
[ 4888.531393] Hello, Kernel!
[ 4888.531403] cdev_kalpit - Major Device Number: 241
[ 4933.677730] cdev_kalpit - read is called

ubuntu@primary:~/ldd/cdev$ sudo ls -l /dev/hello*
crw-r--r-- 1 root root 241,   0 Mar 27 13:05 /dev/hello0
crw-r--r-- 1 root root 241, 128 Mar 27 13:19 /dev/hello128

ls linux-<ver>/scripts/checkpatch.pl
coding style guidelines
