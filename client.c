/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:10:59 by dcampas-          #+#    #+#             */
/*   Updated: 2025/02/25 11:38:57 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_ack = 0;

//El cliente espere confirmaciones despues de cada bit
void	handle_sigusr1(int sig)
{
	(void)sig;
	g_ack = 1;
}

static int	wait_for_response(void)
{
	int	timeout;

	timeout = 0;
	while (!g_ack && timeout < 5)
	{
		usleep(200000);
		timeout++;
	}
	return (g_ack);
}

static int	is_digit_compro(char *argv)
{
	int	i;

	i = 0;
	if (argv == NULL || argv[0] == '\0')
	{
		ft_printf(NUMBER_PID);
		return (0);
	}
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
		{
			ft_printf(NUMBER_PID);
			return (0);
		}
		i++;
	}
	return (1);
}

void	send_char(pid_t pid, char c)
{
	int	i;

	i = 8;
	while (i--)
	{
		g_ack = 0;
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!wait_for_response())
		{
			ft_printf(ERROR_PID);
			exit(1);
		}
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*msg;

	if (argc == 3)
	{
		if (!is_digit_compro(argv[1]))
			return (1);
		pid = (pid_t)ft_atoi(argv[1]);
		msg = argv[2];
		signal(SIGUSR1, handle_sigusr1);
		while (*msg)
		{
			send_char(pid, *msg++);
		}
		send_char (pid, '\0');
		ft_printf("Message sent!\n");
	}
	else
		ft_printf(ERROR_MSG);
}
