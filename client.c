/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:41:56 by aperrein          #+#    #+#             */
/*   Updated: 2023/03/16 13:41:27 by aperrein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft/libft.h"

void	msg(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (sig == SIGUSR1)
	{
		ft_printf("Message bien recu de la part du serveur %d.\n", info->si_pid);
		exit(1);
	}
}

void	bien_recu(void)
{
	struct sigaction	sigact;

	sigact.sa_sigaction = msg;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, 0);
	sigaction(SIGUSR2, &sigact, 0);
	pause();
}

void	f_kill(int pid, int sig)
{
	if (kill(pid, sig) == -1)
	{
		ft_printf("Error, check server PID\n");
		exit(1);
	}
}

void	envoie(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & 128)
			f_kill(pid, SIGUSR2);
		else
			f_kill(pid, SIGUSR1);
		c <<= 1;
		bit++;
		bien_recu();
	}
}

int	main(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argc == 3)
	{
		ft_printf("mon PID %d\n", getpid());
		while (argv[2][i])
		{
			envoie(ft_atoi(argv[1]), argv[2][i]);
			i++;
		}
		envoie(ft_atoi(argv[1]), 0);
		bien_recu();
	}
	else
	{
		ft_printf("Misuse of this program.\nCorrect use :\n");
		ft_printf("./client \"server PID\" \"Your message\"\n");
		return (1);
	}
	return (0);
}
