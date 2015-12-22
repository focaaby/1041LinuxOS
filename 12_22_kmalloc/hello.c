#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");


struct student {
	int age;
	char name[10];
};

struct student *ptr;
struct student *ptr_tmp;
 
static int __init hello_init(void) {
	int i;
	int myage = 22;
	char myname[] = "MaoLin"; 
	printk(KERN_INFO "MAOLIN_Hello\n");
	ptr = kmalloc( sizeof(struct student)*10 , GFP_KERNEL);
	printk(KERN_INFO "MAOLIN, This is using kmalloc()");
	printk(KERN_INFO "MAOLIN, And this pages address:0x%lx\n",(unsigned long)ptr);
	
	if(ptr != NULL) {
		ptr_tmp = ptr;
		for(i = 0; i < 10; i++) {
			ptr->age = myage + i;
			strcpy(ptr->name, myname);
			printk(KERN_INFO "MAOLIN, age:%d, name: %s", ptr->age, ptr->name);
			printk("%d\n", i);
			ptr++;
		}
	}
        return 0;
}

static void __exit hello_exit(void) {
	printk(KERN_INFO "MAOLIN_Goodbye\n");
	kfree(ptr_tmp);
}
 
module_init(hello_init);
module_exit(hello_exit);
