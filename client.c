/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:10:59 by dcampas-          #+#    #+#             */
/*   Updated: 2025/02/21 13:26:20 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_ack = 0;

//El cliente espere confirmaciones despues de cada bit
void	sig_ack(int sig)
{
	(void)sig;
	g_ack = 1;
}

void	send_char(pid_t pid, char c)
{
	int	i = 8;
	int ack_count = 0;

	while (i--)
	{
		g_ack = 0;
		if ((c >> i ) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);

		while (!g_ack)
			pause();

		ack_count++;
	}
	if (ack_count != 8)
		printf("Error: No se recibieron los 8 bits correctamente.\n");
}

int	main(int argc, char **argv)
{	
	pid_t	pid;
	char	*msg;
	
	if (argc == 3)
	{
		if (!atoi(argv[1]))
		{
			printf(NUMBER_PID);
			return (1);
		}
		pid = (pid_t)atoi(argv[1]);
		msg = argv[2];
		signal(SIGUSR1, sig_ack);
		while (*msg)
		{
			send_char(pid, *msg++);
		}
		send_char (pid, '\0');
	}
	else
		printf(ERROR_MSG);
}