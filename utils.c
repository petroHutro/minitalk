/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coleta <coleta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:45:15 by coleta            #+#    #+#             */
/*   Updated: 2022/06/04 20:10:35 by coleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// void	*ft_memset(void *b, int c, size_t len)
// {
// 	while (len--)
// 		((unsigned char *)b)[len] = (unsigned char)c;
// 	return (b);
// }

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

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

void	kills(pid_t pid, int sigusr)
{
	if (kill(pid, sigusr))
		putstr_error("Signal error\n");
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

int	ft_atoi(const char *str)
{
	int			i;
	long int	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] != '\0' && (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
		i++;
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
		if ((res * sign) > 2147483647)
			return (-1);
		if ((res * sign) < -2147483648)
			return (0);
	}
	return (res * sign);
}
