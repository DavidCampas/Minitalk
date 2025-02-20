/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:45:58 by dcampas-          #+#    #+#             */
/*   Updated: 2025/02/20 17:45:16 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(pid_t pid, char c)
{
	int 	i;
	
	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
	}
}

int main(int argc, char **argv)
{
	pid_t	pid = atoi(argv[1]);
	char *msg = argv[2];
	if (argc != 3)
	{
		printf("Uso: %s <PID> <mensaje>\n", argv[0]);
		return (1);
	}
	while (*msg)
	{
		send_char(pid, *msg);
		printf("Enviando caracter... %c\n", *msg);
		msg++;
	}
	send_char(pid, '\0');
	printf("Mensaje enviado\n");
	return (0);
}
