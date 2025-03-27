#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/seq_file.h>
#include <asm/param.h>

#define BUFFER_SIZE 128

#define PROC_NAME "seconds"


unsigned long start_jiffies;
unsigned long end_jiffies;
unsigned long duration;
unsigned long seconds;

static ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos);

static const struct proc_ops proc_ops = {
		    .proc_read = proc_read,
};

static int proc_init(void) {
	start_jiffies = jiffies;
	proc_create(PROC_NAME, 0666, NULL, &proc_ops);
	printk(KERN_INFO "/proc/%s created.\n", PROC_NAME);

	return 0;
}

static void proc_exit(void) {
	end_jiffies = jiffies;
	remove_proc_entry(PROC_NAME, NULL);
	duration  = end_jiffies - start_jiffies;
	printk(KERN_INFO "/proc/%s removed. Total time elapes %lu s.\n", PROC_NAME, duration / HZ);
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
	duration = jiffies - start_jiffies;
	seconds = duration / HZ;
	rv = sprintf(buffer, "From the kernal module was loaded, time had elaped %lu s.\n", seconds);

	if (copy_to_user(usr_buf, buffer, rv)) {
		rv = -EFAULT;
	}

	return rv;
}


module_init( proc_init );
module_exit( proc_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Fd Gong's bf");
MODULE_AUTHOR("SGG");
