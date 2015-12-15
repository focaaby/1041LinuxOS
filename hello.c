#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>

MODULE_LICENSE("GPL");


struct student {
	int age;
	char name[10];
};

struct student *kernelpagemem;
struct student *kernelpagemem_tmp;
 
static int __init hello_init(void) {
	int i;
	int myage = 22;
	char myname[] = "MaoLin"; 
	printk(KERN_INFO "MAOLIN_Hello\n");
	kernelpagemem = (struct student *) __get_free_pages(GFP_KERNEL, 0);
	kernelpagemem_tmp = kernelpagemem;
	printk(KERN_INFO "MAOLIN, And this pages address:0x%lx\n",(unsigned long)kernelpagemem);
	
	if(kernelpagemem != NULL) {
		for(i = 0; i < 4; i++) {
			kernelpagemem->age = myage + i;
			strcpy(kernelpagemem->name, myname);
			printk(KERN_INFO "MAOLIN, age:%d, name: %s", kernelpagemem->age, kernelpagemem->name);
			printk("%d\n", i);
			kernelpagemem++;
		}
	}
        return 0;
}

static void __exit hello_exit(void) {
	printk(KERN_INFO "MAOLIN_Goodbye\n");
	free_page((unsigned long)kernelpagemem_tmp);
}
 
module_init(hello_init);
module_exit(hello_exit);
