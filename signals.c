#include <signal.h>
#include <unistd.h>
#include <stdio.h>


/*int	kill(pid_t pid, int sig)
{
	kill(12345, SIGUSR1);	//Envia SIGURSR1 al proceso con PID 12345
}

void	(*signal(int signum, void (*handeler)(int)))(int);
*/

void	handler_signal(int signum)
{
	if (signum == SIGUSR1)
		printf("Recibí señal SIGUSR1\n");
	else if (signum == SIGUSR2)
		printf("Recibí señal SIGUSR2\n");
}
void	chartobit(char c)
{
	int i = 8;
	char bits;

	while (i--)
	{
		if ((c >> i) & 1)
			write (1, "1", 1);
		else
			write (1, "0", 1);	
	}
	write(1, " ", 1);
}

int main()
{
	printf("PID del proceso: %d\n", getpid());
	
	signal(SIGUSR1, handler_signal);
	signal(SIGUSR2, handler_signal);

	while (1)
	{
		printf("Esperando señales...\n");
		sleep(1);
	}
	return (0);
	

	chartobit('A');
	chartobit('B');
	chartobit('C');
	
	return (0);
}
