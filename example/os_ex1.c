#include <stdio.h>
void main() {
	int pid = 0;
	pid = fork();   // two process, run queue 
	if (pid == 0) { // fork() == 0 -> child  
		// the PID of the child process is returned in the parent, and 0 is returned in the child 
		//printf("My PID is %d and my parent's ID %d\n",getpid(),getppid());
		printf("(A) child: pid = %d\n",pid);
		printf("(B) child: pid1 = %d\n",getpid());
	} else { // fork() > 0  -> parent
		//printf("My PID is %d and my parent's ID %d\n",getpid(),getppid());
		printf("(C) parent: pid = %d\n",pid);
		printf("(D) parent: pid1 = %d\n",getpid());
		wait(NULL); // wait for child process end: 
	}
	//printf("\nMy PID is %d and my parent's ID %d\n",getpid(),getppid());
}
