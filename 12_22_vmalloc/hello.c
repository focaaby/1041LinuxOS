#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/vmalloc.h>

MODULE_LICENSE("GPL");


struct student {
	int age;
	char name[10];
};

struct student *buf;
struct student *buf_tmp;
 
static int __init hello_init(void) {
	int i;
	int myage = 22;
	char myname[] = "MaoLin"; 
	printk(KERN_INFO "MAOLIN_Hello\n");
	buf = vmalloc(1 * PAGE_SIZE);
	printk(KERN_INFO "MAOLIN, This is using vmalloc()");
	printk(KERN_INFO "MAOLIN, And this pages address:0x%lx\n",(unsigned long)buf);
	
	if(buf != NULL) {
		buf_tmp = buf;
		for(i = 0; i < 10; i++) {
			buf->age = myage + i;
			strcpy(buf->name, myname);
			printk(KERN_INFO "MAOLIN, age:%d, name: %s", buf->age, buf->name);
			printk("%d\n", i);
			buf++;
		}
	}
        return 0;
}

static void __exit hello_exit(void) {
	printk(KERN_INFO "MAOLIN_Goodbye\n");
	vfree(buf_tmp);
}
 
module_init(hello_init);
module_exit(hello_exit);
