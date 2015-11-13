/**
 * A pthread program illustrating how to
 * create a simple thread and some of the pthread API
 * This program implements the summation function where
 * the summation operation is run as a separate thread.
 * Usage on Solaris/Linux/Mac OS X:
 *
 * gcc thrd.c -lpthread
 * a.out <number>
 **/

#include <sys/syscall.h>
#include <pthread.h>
#include <stdio.h>
int sum; /* this data is shared by the thread(s) */
void *runner(void *param); /* the thread */

main(int argc, char *argv[])
{
	pthread_t tid; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */
	pid_t gettid(void);
	if (argc != 2) {
		fprintf(stderr,"usage: a.out <integer value>\n");
		exit(0);
	}
	if (atoi(argv[1]) < 0) {
		fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
		exit(0);
	}
	// print the thread ID...
	printf("MAIN: My PID is %d and my parent's ID %d\n",getpid(), getppid());
	printf("MAIN: pthread ID %u \n", (unsigned int)pthread_self());
	//printf("MAIN: thread ID %d \n", gettid());
	pid_t test = syscall(SYS_gettid);
//	pid_t test = (pid_t) syscall(SYS_gettid);
	printf("MAIN: thread ID %d\n", test);
	

	/* get the default attributes */
	pthread_attr_init(&attr);
	/* create the thread */
	pthread_create(&tid,&attr,runner,argv[1]);
	/* now wait for the thread to exit */
	pthread_join(tid,NULL);
	printf("sum = %d\n",sum);
}


/**
 * The thread will begin control in this function
 */
void *runner(void *param) 
{
	int upper = atoi(param);
	int i;
	sum = 0;	
	if (upper > 0) {
		for (i = 1; i <= upper; i++)
			sum += i;
	}
	printf("RUNNER: My PID is %d and my parent's ID %d\n",getpid(), getppid());
	printf("RUNNER: pthread ID %u \n", (unsigned int)pthread_self());
	pid_t runnerid = (pid_t) syscall (SYS_gettid);
	printf("RUNNER: thread ID %d\n", runnerid);
	pthread_exit(0);
}
