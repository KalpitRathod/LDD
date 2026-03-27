/*

*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

static int major;

static ssize_t driver_read (struct file *f, char __user *u, size_t l, loff_t *o){
    printk("cdev_kalpit - read is called\n");
    return 0;
}

static struct file_operations fops = {
    .read = driver_read
};

static int __init driver_init(void){ 
    printk("Hello, Kernel!\n");
    major = register_chrdev(0, "cdev_kalpit", &fops);
    //0(dunamic allocation)-find device number available to allocate but eg. 64 will retun all 0-255 device number to us

    if (major<0){
        printk("cdev_kalpit - Error registering chrdev\n");
        return major;
    }
        printk("cdev_kalpit - Major Device Number: %d\n", major);

    return 0;
}

static void __exit driver_exit(void){
    unregister_chrdev(major, "cdev_kalpit"); //this will delete the character device and free the device number
    printk("Goodbye, Kernel!\n");
}

module_init(driver_init);
module_exit(driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kalpit Rathod <99kalpitrathod@gmail.com>");
MODULE_DESCRIPTION("A sample driver for registering a character device");