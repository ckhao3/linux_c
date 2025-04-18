#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

static int intval;
module_param(intval, int, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(intval, ".e.g. intval = 1")

static int array[5] = {0};
static int array_size;
module_param_array(array, int, &array_size, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(array, ".e.g. array = 1,3,4")

static char strval[20];
module_param_string(str, strval, sizeof(strval), S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(str, ".e.g. str = 123123")

static int __init helloworld_init(void)
{
    int i = 0;
    printk("intval is %d", intval);
    for (; i < array_size; i++)
        printk("%d\n", array[i]);

    printk("str = %s\n", strval);
    return 0;
}

static void __exit helloworld_exit(void)
{
    printk("params bye!\n");
}

module_init(helloworld_init);
module_exit(helloworld_exit);

MODULE_LICENSE("GPL");
MODULE_INFO(intree, "N");
MODULE_AUTHOR("qgz");
MODULE_VERSION("v1.0");
