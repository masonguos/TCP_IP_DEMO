#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREAD 100

void *pthread_des(void *arg);
void *pthread_inc(void *arg);
long long num = 0;
pthread_mutex_t mutex;


int main(int argc, char **argv)
{
	pthread_t thread_id[NUM_THREAD];
	int i;

	pthread_mutex_init(&mutex, NULL);

	for (i = 0; i < NUM_THREAD; i++) {
		if (i%2)
			pthread_create(&(thread_id[i]), NULL, pthread_des, NULL);
		else
			pthread_create(&(thread_id[i]), NULL, pthread_inc, NULL);
	}

	for (i = 0; i < NUM_THREAD; i++) {
		pthread_join(thread_id[i], NULL);
	}
	printf("resule:	%lld \n", num);
	pthread_mutex_destroy(&mutex);
	return 0;
}

void *pthread_des(void *arg)
{
	pthread_mutex_lock(&mutex);
	for (int i = 0; i < 50000000; i++)
		num++;
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void *pthread_inc(void *arg)
{	
	pthread_mutex_lock(&mutex);		
	for (int i = 0; i < 50000000; i++){
		num--;
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

