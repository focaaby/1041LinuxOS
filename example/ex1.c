#include <stdio.h>
void main() {
	int ret = 0;
	int num=7; 
	num --;
	ret = fork();   // two process, run queue 
	num --;
	if (ret == 0) { // fork() == 0 -> child  
		// the PID of the child process is returned in the parent, and 0 is returned in the child 
		num --;
		printf("(b) %d ", num);
		printf("\nMy PID is %d and my parent's ID %d\n",getpid(),getppid());
		num --;
	} else { // fork() > 0  -> parent
		num --; 
		wait(NULL); // wait for child process end: 
		num --;
		printf("(d) %d ", num);
		printf("\nMy PID is %d and my parent's ID %d\n",getpid(),getppid());
		num --;
	}
	num --;
	printf("(e) %d ", num);
	printf("\nMy PID is %d and my parent's ID %d\n",getpid(),getppid());
}
