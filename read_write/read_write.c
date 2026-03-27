#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

static int major;
static char text[64];

//this functions returns the amount of byte read successfully
static ssize_t driver_read (struct file *filp, char __user *user_buf, size_t l, loff_t *o){
    //struct file represent the open file in the linux kernel
    //other argument is the pointer that points at user space buffer
    pr_info("cdev_kalpit - read is called\n");
    return 0;
}

static struct file_operations fops = {
    .read = driver_read
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