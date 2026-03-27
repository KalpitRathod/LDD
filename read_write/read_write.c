/*
some necessary commands
ubuntu@primary:~/ldd/read_write$ sudo rm /dev/hello0 //deleting the files

unregister_chrdev(241, "cdev_kalpit"); manually unregistering entries

ubuntu@primary:~/ldd/read_write$ sudo mknod /dev/hello0 c 241 0 //again adding 

*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

static int major;
static char text[64];

//this functions returns the amount of byte read successfully
static ssize_t driver_read (struct file *filp, char __user *user_buf, size_t len, loff_t *off){
    //struct file represent the open file in the linux kernel
    //user buffer argument is the pointer that points at user space buffer in which we want to have the data after we are done with the read function
    //size_t is the length of the buffer
    //loff_t pointer gives us our current file offset
    // off after we read 10 bytes from user we need to increase this pointer by 10 so in this case you can 

    int not_copied, delta, to_copy = (len + *off) < sizeof(text) ? len : (sizeof(text) - *off);

    pr_info("cdev_kalpit - Read is called, we want to read %ld bytes, but actually only copying %d bytes. The offset is %lld\n", len, to_copy, *off);

    if(*off >= sizeof(text))
        return 0;

    not_copied = copy_to_user(user_buf, &text[*off], to_copy);
    delta = to_copy-not_copied;
    if (not_copied)
        pr_warn("cdev_kalpit - could only copy %d bytes\n", delta);

    *off += delta;
    
    return delta;

    /*
    1. The "Safe" Read
    If (len + *off) < sizeof(text), it means the user's request fits perfectly within the remaining space of your buffer.

    Result: to_copy = len.

    2. The "Boundary" Read
    If the user asks for more than what's left (or exactly what's left), the condition is false. We must "cap" the read so we don't go out of bounds.

    Result: to_copy = (sizeof(text) - *off). This calculates the remaining distance from the current offset to the very end of the buffer.
    
    A Visual Representation
    Imagine your text buffer is 50 bytes long, and the user has already read 40 bytes (so *off = 40).

    User Request (len), | Calculation, | Logic,                               | Final to_copy
    5 bytes,            | (5+40)<50,   | True: The data fits.,                | 5
    20 bytes,           | (20+40)<50,  | False: There are only 10 bytes left!,| 10
    */
}


static ssize_t driver_write (struct file *filp, const char __user *user_buf, size_t len, loff_t *off){

    int not_copied, delta, to_copy = (len + *off) < sizeof(text) ? len : (sizeof(text) - *off);
    pr_info("cdev_kalpit - Write is called, we want to write %ld bytes, but actually only copying %d bytes. The offset is %lld\n", len, to_copy, *off);

    if(*off >= sizeof(text))
        return 0;

    not_copied = copy_from_user(&text[*off], user_buf, to_copy);
    delta = to_copy-not_copied;
    if (not_copied)
        pr_warn("cdev_kalpit - could only copy %d bytes\n", delta);

    *off += delta;
    
    return delta;
}

static struct file_operations fops = {
    .read = driver_read,
    .write = driver_write
};

static int __init driver_init(void){ 
    printk("Hello, Kernel!\n");
    major = register_chrdev(0, "cdev_kalpit", &fops);

    if (major<0){
        pr_err("cdev_kalpit - Error registering chrdev\n");
        return major;
    }
    printk("cdev_kalpit - Major Device Number: %d\n", major);

    return 0;
}

static void __exit driver_exit(void){
    unregister_chrdev(major, "cdev_kalpit");
    printk("Goodbye, Kernel!\n");
}

module_init(driver_init);
module_exit(driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kalpit Rathod <99kalpitrathod@gmail.com>");
MODULE_DESCRIPTION("A sample driver for registering a character device");