/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coleta <coleta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:45:30 by coleta            #+#    #+#             */
/*   Updated: 2022/06/06 20:53:37 by coleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_signal;

int	wait_sig(int wait)
{
	while (g_signal == 1)
	{
		if (wait > 9999)
			putstr_error("Waiting too long\n");
		usleep(5);
		wait += 5;
	}
	return (wait);
}

void	send_message(int pid, char *str)
{
	int	i;
	int	wait;
	int	len;

	len = ft_strlen(str) + 1;
	while (len --)
	{
		i = 8;
		while (i --)
		{
			g_signal = 1;
			wait = 0;
			if (*str >> i & 1)
				kills(pid, SIGUSR2);
			else
				kills(pid, SIGUSR1);
			wait = wait_sig(wait);
		}
		++ str;
	}
}

static void	ft_signals(int signal, siginfo_t *sigingo, void *context)
{
	(void)sigingo;
	(void)context;
	g_signal = 0;
	if (signal == SIGUSR1)
		ft_putstr_fd("Messange send\n", 1);
}

static int	signal_init(struct sigaction *sig)
{
	sigset_t	block;

	if (sigemptyset(&block) < 0 || sigaddset(&block, SIGUSR1) < 0 || \
	sigaddset(&block, SIGUSR2) < 0)
		putstr_error("Mask error\n");
	sig->sa_mask = block;
	sig->sa_flags = SA_SIGINFO;
	sig->sa_sigaction = ft_signals;
	if ((sigaction(SIGUSR1, sig, NULL) < 0) || \
	(sigaction (SIGUSR2, sig, NULL) < 0))
		putstr_error("Signnal error\n");
	return (1);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sig;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid > 0)
		{
			if (signal_init(&sig))
				send_message(pid, argv[2]);
		}
		else
			putstr_error("PID error\n");
	}
	else
		putstr_error("Argument error\n");
	return (0);
}
