#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init helloworld_init(void)
{
    printk("helloworld!\n");
    return 0;
}

static void __exit helloworld_exit(void)
{
    printk("helloworld bye!\n");
}

module_init(helloworld_init);
module_exit(helloworld_exit);

MODULE_LICENSE("GPL");
MODULE_INFO(intree, "N");
MODULE_AUTHOR("qgz");
MODULE_VERSION("v1.0");
