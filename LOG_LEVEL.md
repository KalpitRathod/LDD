search the kerne log levels 
its like 
printk(KERN_INFO "Goodbye, Kernel!\n");
there are 7 levels , default and cont

you can in dmesg only list out the certain log level messages
eg. sudo dmesg -l 7 