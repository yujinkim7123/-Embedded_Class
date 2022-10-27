#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>

#define NOD_MAJOR 100
#define NOD_NAME "nobrand"

MODULE_LICENSE("GPL");

static int nobrand_open(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "welcome\n");
    return 0;
}

static int nobrand_release(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "release\n");
    return 0;
}

static void ledon(void)
{
    printk(KERN_INFO "LED ON\n");
}

static void ledoff(void)
{
    printk(KERN_INFO "LED OFF\n");
}

static long nobrand_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    switch (cmd)
    {
        case _IO(0, 3):
            ledon();
            break;
        case _IO(0, 4):
            ledoff();
            break;
    }
    return 0;
}

static struct file_operations fops = {
    .open = nobrand_open,
    .release = nobrand_release,
    .unlocked_ioctl = nobrand_ioctl,
};

static int nobrand_init(void)
{
    if (register_chrdev(NOD_MAJOR, NOD_NAME, &fops) < 0)
    {
        printk("INIT FALE\n");
    }

    printk(KERN_INFO "hi\n");
    return 0;
}

static void nobrand_exit(void)
{
    unregister_chrdev(NOD_MAJOR, NOD_NAME);
    printk(KERN_INFO "bye\n");
}

module_init(nobrand_init);
module_exit(nobrand_exit);
