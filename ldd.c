#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kalpit Rathod");
MODULE_DESCRIPTION("First Dynamically Loadable Kernel Module.");

static int my_module_init_function (void) {
    printk("Hello World!\n");
    return 0;
}

static void my_module_exit_function (void) {
    printk("Good, Bye!\n");
}

module_init(my_module_init_function);
module_exit(my_module_exit_function);