#include <linux/module.h>
#include <linux/init.h>

static int __init driver_init(void){ //static so out side this program no one can access our code
    printk(KERN_INFO "Hello, Kernel!\n");
    printk(KERN_INFO " This is an info\n"); //these are the log levels
    printk(KERN_WARNING " This is an warning\n");
    printk(KERN_ALERT " This is an alert\n");
    printk(KERN_DEBUG " This is an debug\n");
    printk(KERN_INFO " This is an Info\n");
    return 0;
}

//__init and __exit macros will just improve our readibility and do nothing at all
static void __exit driver_exit(void){
    printk(KERN_INFO "Goodbye, Kernel!\n");
    pr_emerg("log_level - emergancy"); //these are the log levels
    pr_err("log_level - error");
    pr_info("log_level - infor");
}

module_init(driver_init);
module_exit(driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kalpit Rathod <99kalpitrathod@gmail.com>"); //author macro
MODULE_DESCRIPTION("A simple hello world Linux Kernel Module"); //author macro