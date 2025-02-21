/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:13:29 by dcampas-          #+#    #+#             */
/*   Updated: 2025/02/21 13:17:38 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int	bit = 0;
	static char	c = 0;

	(void)context;

	if (sig == SIGUSR1)
		c |= (1 << (7 - bit));
	bit++;

	if (bit == 8)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write (1, &c, 1);
		bit = 0;
		c = 0;
	}
	if (info->si_pid > 0)
		kill (info->si_pid, SIGUSR1);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		(void)argv;
		struct	sigaction sa;
	
		printf("PID del proceso es: %d\n", getpid());

		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = handle_signal;
		sigemptyset(&sa.sa_mask);

		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	
		while (1)
			pause ();
		return (0);
	}
	else
	{
		printf(WRONG_ARG_SERV);
		return (1);
	}
}