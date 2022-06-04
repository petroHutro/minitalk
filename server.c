/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coleta <coleta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:45:21 by coleta            #+#    #+#             */
/*   Updated: 2022/06/04 20:23:24 by coleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	get_massage(int signal, siginfo_t *sigingo, void *context)
{
	static int				i = 0;
	static unsigned char	c = 0;

	// printf("%d\n", signal);
	(void) context;
	c |= (signal == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			ft_putchar_fd('\n', 1);
			kills(sigingo->si_pid, SIGUSR1);
			return ;
		}
		write(1, &c, 1);
		c = 0;
	}
	else
		c <<= 1;
	kills(sigingo->si_pid, SIGUSR2);
}

static int	signal_init(struct sigaction *sig)
{
	sigset_t	block;

	if (sigemptyset(&block) < 0 || sigaddset(&block, SIGUSR1) < 0 || sigaddset(&block, SIGUSR2) < 0)
		putstr_error("Mask error\n");
	// ft_memset(sig, 0, sizeof(struct sigaction));
	sig->sa_mask = block;
	sig->sa_flags = SA_SIGINFO;
	sig->sa_sigaction = get_massage;
	if ((sigaction(SIGUSR1, sig, NULL) < 0) || (sigaction (SIGUSR2, sig, NULL) < 0))
		putstr_error("Signnal error\n");
	return (1);
}

int	main()
{
	struct sigaction	sig;

	if (signal_init(&sig))
	{
		ft_putstr_fd("PID: ", 1);
		ft_putnbr_fd(getpid(), 1);
		ft_putchar_fd('\n', 1);
		while (1)
			pause();
	}
}
