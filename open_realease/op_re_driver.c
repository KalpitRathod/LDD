/*
ubuntu@primary:~/ldd/open_realease$ sudo mknod /dev/hello0 c 240 0
ubuntu@primary:~/ldd/open_realease$ sudo ./cdev_test /dev/hello0

[12679.913043] cdev_kalpit - Major: 240, Minor: 0
[12679.913050] cdev_kalpit - filp->f_pos 0
[12679.913053] cdev_kalpit - filp->f_mode 0x1d
[12679.913054] cdev_kalpit - filp->f_flags 0x8000
[12679.913058] cdev_kalpit - File is closed.
[12679.913062] cdev_kalpit - Major: 240, Minor: 0
[12679.913064] cdev_kalpit - filp->f_pos 0
[12679.913066] cdev_kalpit - filp->f_mode 0x1f
[12679.913067] cdev_kalpit - filp->f_flags 0x109002
[12679.913070] cdev_kalpit - File is closed.
[12679.913074] cdev_kalpit - Major: 240, Minor: 0
[12679.913076] cdev_kalpit - filp->f_pos 0
[12679.913078] cdev_kalpit - filp->f_mode 0x1e
[12679.913079] cdev_kalpit - filp->f_flags 0x8801
[12679.913082] cdev_kalpit - File is closed.
*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

static int major;

static int driver_open(struct inode *inode, struct file *filp){
    // arguments inode is kernel structure to represent a file over this inode structure we can get back the major and minor device number of the opened device file
    pr_info("cdev_kalpit - Major: %d, Minor: %d\n", imajor(inode), iminor(inode)); //these are the macros to get the major and minor device number
    //second argument structure represent an open file in the linux kernel 
    //object of the structure is created when we are opening a file and before we are calling open callback function it destroys after we call the release function
    // f_mode permission for file like read or write
    // f_op contains file operations
    // void pointer to private data
    // f_pos current position to open file
    pr_info("cdev_kalpit - filp->f_pos %lld\n", filp->f_pos); //lld long long integer
    pr_info("cdev_kalpit - filp->f_mode 0x%x\n", filp->f_mode); 
    pr_info("cdev_kalpit - filp->f_flags 0x%x\n", filp->f_flags); 

    return 0;
}

static int driver_release(struct inode *inode, struct file *filp){
    pr_info("cdev_kalpit - File is closed.\n"); 
    return 0;
}


static struct file_operations fops = {
   .open = driver_open,
   .release = driver_release,
};

static int __init driver_init(void){ 
    printk("Hello, Kernel!\n");
    major = register_chrdev(0, "cdev_kalpit", &fops);

    if (major<0){
        pr_err("cdev_kalpit - Error registering chrdev\n");
        return major;
    }
        pr_info("cdev_kalpit - Major Device Number: %d\n", major);

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

/*
Decoding the Kernel Logs
Each block of logs represents one of the three open() calls in your C program.

1. The First Open (O_RDONLY)
f_mode 0x1d: This indicates "Read" permission.

f_flags 0x8000: This matches O_RDONLY. (In Linux kernels, O_RDONLY is often defined as 0, but additional internal flags like O_LARGEFILE are often automatically added by the system, resulting in 0x8000).

File is closed: This confirms your close(fd) in User Space triggered driver_release.

2. The Second Open (O_RDWR | O_SYNC)
f_mode 0x1f: Notice it changed from 0x1d to 0x1f. The addition of 0x2 in hex represents the Write permission being added to the Read permission.

f_flags 0x109002: This is much larger because it includes O_SYNC. The kernel is now aware that any data sent to this driver should bypass caches and go straight to the "hardware."

3. The Third Open (O_WRONLY | O_NONBLOCK)
f_mode 0x1e: This represents Write-Only (no Read bit).

f_flags 0x8801: This contains the bit for O_NONBLOCK. If your driver had a read function, it would see this flag and know not to make the user wait if no data was ready.

The Big Picture: How it Linked
By running sudo mknod /dev/hello0 c 240 0, you created a "Phone Number" for your driver:

/dev/hello0: The name the user program uses.

c: Tells the system it's a Character device.

240: The Major Number—the unique ID that points directly to your loaded kernel module.

0: The Minor Number—used if your driver manages multiple similar devices (like four different serial ports).
*/