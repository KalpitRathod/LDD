#include <linux/module.h>
#include <linux/init.h>

int driver_init(void){
    printk("Hello, Kernel!\n");
    return 0;
}

void driver_exit(void){
    printk("Goodbye, Kernel!\n");
}

module_init(driver_init);
module_exit(driver_exit);

MODULE_LICENSE("GPL");