/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coleta <coleta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:58:12 by coleta            #+#    #+#             */
/*   Updated: 2022/06/07 16:43:28 by coleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s && fd)
		write(fd, s, ft_strlen(s));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	putstr_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, &"-", 1);
		ft_putnbr_fd(2, fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		write(fd, &"-", 1);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n % 10 + 48, fd);
}
