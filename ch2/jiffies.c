#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>

#include <linux/jiffies.h>

#define BUFFER_SIZE 128

#define MESSAGE "This is writen by ur label"

// protytypes
static ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos);


static const struct proc_ops proc_ops = {
	.proc_read = proc_read,
};


static int proc_init(void) {
	// create a auth:0666 jiffies proc
	proc_create("jiffies", 0666, NULL, &proc_ops);
	printk(KERN_INFO "/proc/jiffies created...\n");
	return 0;
}

static void proc_exit(void) {
	remove_proc_entry("jiffies", NULL);
	printk(KERN_INFO "/proc/jiffies removed...\n");
}

static ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {
	int rv = 0;
	char buffer[BUFFER_SIZE];
	static int completed = 0;

	if (completed) {
		completed = 0;
		return 0;
	}
	
	completed = 1;
	rv = sprintf(buffer, "current jeffies is %lu\n", jiffies);

	if (copy_to_user(usr_buf, buffer, rv)) {
		rv = -EFAULT;
	}

	return rv;
}

module_init(proc_init);
module_exit(proc_exit);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Fd Gong");
MODULE_AUTHOR("SGG");

