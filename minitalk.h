/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coleta <coleta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:45:25 by coleta            #+#    #+#             */
/*   Updated: 2022/06/04 20:06:49 by coleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
#define MINITALK_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

// typedef struct s_message
// {
// 	char			*text;
// 	int				i;
// 	unsigned char	c;
// 	int				size;
// }	t_message;

void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen(const char *str);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);
void	putstr_error(char *str);
void	kills(pid_t pid, int sigusr);
void	*ft_memset(void *b, int c, size_t len);

#endif