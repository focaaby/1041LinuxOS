#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/kthread.h>

int *ptr = NULL;

static int MAOLIN_thread(void *arg) {
        printk("This is in MAOLIN_thread\n");
	
	ptr = (int *)kmalloc(1000, GFP_KERNEL);
	ptr[2] = 9999;
	printk("MAOLIN, This ptr[3] is %d\n", ptr[2]); 

	do {
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
	} while(1);

	return 0;
}
 
static int __init hello_init(void) {
	kthread_run(MAOLIN_thread, NULL, "MAOLIN_thread");
        return 0;
}

static void __exit hello_exit(void) {
	printk(KERN_INFO "MAOLIN_Goodbye\n");
}
 
module_init(hello_init);
module_exit(hello_exit);
