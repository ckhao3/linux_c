#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/moduleparam.h>

static int major = 0;
static int minor = 0;
static dev_t dev_num;

module_param(major, int, S_IRUGO);
module_param(minor, int, S_IRUGO);

static int __init helloworld_init(void)
{
    int ret;

    if (major)
    {
        printk("major is %d\n", major);
        printk("minor is %d\n", minor);
        dev_num = MKDEV(major, minor);
        ret = register_chrdev_region(dev_num, 1, "chrdev_name");
        if (ret < 0)
        {
            printk("chrdev failure\n");
            return 1;
        }
        printk("chrdev success\n");
    }
    else
    {
        ret = alloc_chrdev_region(&dev_num, 0, 1, "alloc_name");
        if (ret < 0)
        {
            printk("alloc failure\n");
            return 1;
        }
        printk("alloc success\n");
        major = MAJOR(dev_num);
        minor = MINOR(dev_num);
        printk("major is %d\n", major);
        printk("minor is %d\n", minor);
    }

    return 0;
}

static void __exit helloworld_exit(void)
{
    unregister_chrdev_region(dev_num, 1);
    printk("dev_t bye!\n");
}

module_init(helloworld_init);
module_exit(helloworld_exit);

MODULE_LICENSE("GPL");
MODULE_INFO(intree, "N");
MODULE_AUTHOR("qgz");
MODULE_VERSION("v1.0");
