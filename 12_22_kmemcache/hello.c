#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

struct student {
	int age;
	char name[10];
};

struct kmem_cache *buf_cache = NULL;
struct student *buf[10];
 
static int __init hello_init(void) {
	int i;
	int myage = 22;
	char myname[] = "MaoLin"; 
	printk(KERN_INFO "MAOLIN_Hello\n");
	// create the cache
	buf_cache = kmem_cache_create("my_student_cache", sizeof(struct student), ARCH_MIN_TASKALIGN , SLAB_HWCACHE_ALIGN, NULL);
	printk(KERN_INFO "MAOLIN, This is using kmem_cache()");
	
	if(buf_cache != NULL) {
		// allocate 10 times, do not use ++
		for(i = 0; i < 10; i++) {
			buf[i] = kmem_cache_alloc(buf_cache, GFP_KERNEL); 
			buf[i]->age = myage + i;
			strcpy(buf[i]->name, myname);
		}
		// print 
		for(i = 0; i < 10; i++) {
			printk(KERN_INFO "MAOLIN, age:%d, name: %s", buf[i]->age, buf[i]->name);
			printk("%d\n", i);
		}
	}
        return 0;
}

static void __exit hello_exit(void) {
	int i;
	for(i = 0; i < 10; i++) 
		kmem_cache_free(buf_cache, buf);
	printk(KERN_INFO "MAOLIN_Goodbye\n");
}
 
module_init(hello_init);
module_exit(hello_exit);
