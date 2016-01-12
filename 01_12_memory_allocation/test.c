#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int *ptr;
// 	ptr = (int *)malloc(1000);
	ptr[3] = 99;
	printf("This is prt[3]: %d\n", ptr[3]); 

        return 0;
}
