/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coleta <coleta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:45:21 by coleta            #+#    #+#             */
/*   Updated: 2022/06/06 21:03:58 by coleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*add_char(char	*str, char c)
{
	char	*copy;
	size_t	len;
	size_t	i;

	i = -1;
	len = ft_strlen(str);
	copy = (char *)malloc(len + 2);
	if (copy == (void *)0)
		return ((void *)0);
	while (++i < len)
		copy[i] = str[i];
	copy[i] = c;
	copy[++i] = '\0';
	if (str)
		free(str);
	return (copy);
}

static void	get_massage(int signal, siginfo_t *sigingo, void *context)
{
	static t_message	message;

	(void) context;
	if (sigingo->si_pid != 0)
		message.pid = sigingo->si_pid;
	if (!message.i)
		message.i = 0;
	message.c |= (signal == SIGUSR2);
	if (++message.i == 8)
	{
		message.i = 0;
		if (!message.c)
		{
			ft_putchar_fd('\n', 1);
			ft_putstr_fd(message.text, 1);
			free_message(&message);
			kills(message.pid, SIGUSR1);
			return ;
		}
		message.text = add_char(message.text, message.c);//обработать ошибки 
		message.c = 0;
	}
	else
		message.c <<= 1;
	kills(message.pid, SIGUSR2);
}

static int	signal_init(struct sigaction *sig)
{
	sigset_t	block;

	if (sigemptyset(&block) < 0 || sigaddset(&block, SIGUSR1) < 0 \
	|| sigaddset(&block, SIGUSR2) < 0)
		putstr_error("Mask error\n");
	sig->sa_mask = block;
	sig->sa_flags = SA_SIGINFO;
	sig->sa_sigaction = get_massage;
	if ((sigaction(SIGUSR1, sig, NULL) < 0) || \
	(sigaction (SIGUSR2, sig, NULL) < 0))
		putstr_error("Signnal error\n");
	return (1);
}

int	main(void)
{
	struct sigaction	sig;

	if (signal_init(&sig))
	{
		ft_putstr_fd("PID: ", 1);
		ft_putnbr_fd(getpid(), 1);
		while (1)
			pause();
	}
}
