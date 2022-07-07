#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define N 15
#define KEY 13
#define SIZE 4096

void main(int argc, char *argv[]) 
{
	int shmid;
	int pid;
	sem_t *full;
	sem_t *empty;
	sem_t *mutex;
	void *buf;

	shmid = shmget(KEY, SIZE, IPC_CREAT|0666);

	if (shmid == -1) 
	{	
		perror("failed to create shared memory");
		exit(1);
	}

	buf = shmat(shmid, 0, 0);

	if (buf == (void*)-1) 
	{	
		perror("failed to attach memory");
		exit(1);
	}

	full = (sem_t*) buf;
	buf = buf + sizeof(sem_t);
	empty = (sem_t*) buf;
	buf = buf + sizeof(sem_t);
	mutex = (sem_t*) buf;
	buf = buf + sizeof(sem_t);

	if (sem_init(full, 1, 0) < 0) 
	{
		perror("failed to initialize semaphore 'full'");
		exit(1);
	}

	if (sem_init(empty, 1, N) < 0) 
	{
		perror("failed to initialize semaphore 'empty'");
		exit(1);
	}

	if (sem_init(mutex, 1, 1) < 0) 
	{	
		perror("failed to initialize semaphore 'mutex'");
		exit(1);
	}

	pid = fork();

	if (pid == 0) //producer process
	{
		while (1)
		{
			sleep(1);

			if (sem_wait(empty) < 0)
			{
				perror("PRODUCER : failed to decrement semaphore 'empty'");
				exit(1);
			}

			if (sem_wait(mutex) < 0)
			{
				perror("PRODUCER : failed to decrement semaphore 'mutex'");
				exit(1);
			}

			printf("PRODUCER : new item produced\n");

			if (sem_post(mutex) < 0)
			{
				perror("PRODUCER : failed to increment semaphore 'mutex'");
				exit(1);
			}

			if (sem_post(full) < 0)
			{
				perror("PRODUCER : failed to increment semaphore 'mutex'");
				exit(1);
			}	
		}
	}
	else //consumer process
	{
		while (1)
		{
			sleep(rand() % 5);

			if (sem_wait(full) < 0)
			{
				perror("CONSUMER : failed to decrement semaphore 'full'");
				exit(1);
			}

			if (sem_wait(mutex) < 0)
			{
				perror("CONSUMER : failed to decrement semaphore 'mutex'");
				exit(1);
			}

			printf("CONSUMER : an item is consumed\n");

			if (sem_post(empty) < 0)
			{
				perror("CONSUMER : failed to increment semaphore 'empty'");
				exit(1);
			}

			if (sem_post(mutex) < 0)
			{
				perror("CONSUMER : failed to increment semaphore 'mutex'");
				exit(1);
			}
		}
	}	

}


