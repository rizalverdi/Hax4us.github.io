#include <signal.h>
#include <pthread.h>

static void thread_cancel_signal_handler(int sig_num)
{
	if (sig_num == SIGUSR1)
	{
		pthread_exit(0);
	}
}

/* This function can be called in the place of pthread_setcancelstate() and setcanceltype 
*/
/* Note it must be called for cancelable threads */
int thread_cancelable()
{
	struct sigaction action;
	memset(&action, 0, sizeof(action));
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	action.sa_handler = &thread_cancel_signal_handler;

	return sigaction(SIGUSR1, &action, NULL);
}
/* Substitute for pthread_cancel */
int cancel_thread(pthread_t thread)
{
	return pthread_kill(thread, SIGUSR1);
}
