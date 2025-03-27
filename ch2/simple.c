/**
 * simple.c
 *
 * A simple kernel module. 
 * 
 * To compile, run makefile by entering "make"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

// the extra
#include <linux/hash.h>
#include <linux/gcd.h>
#include <asm/param.h>
#include <linux/jiffies.h>


unsigned long start_time;
unsigned long end_time;
unsigned long duration;

/* This function is called when the module is loaded. */
static int simple_init(void)
{
	start_time = jiffies;
  printk(KERN_INFO "Loading Module\n");
	printk(KERN_INFO "%llu\n", GOLDEN_RATIO_PRIME);
	printk(KERN_INFO "start: %lu\n", start_time);
	printk(KERN_INFO "the HZ = %d\n", HZ);
	return 0;
}

/* This function is called when the module is removed. */
static void simple_exit(void) {
	end_time = jiffies;
	duration = end_time - start_time;
	printk(KERN_INFO "Removing Module\n");
	printk(KERN_INFO "The great common divider of 3300 and 24 is %lu\n", gcd(3300, 24));
	printk(KERN_INFO "end: %lu\n", end_time);
	printk(KERN_INFO "HZ=%d, jiffies_diff=%lu, seconds=%lu\n", HZ, duration, duration / HZ);
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

