/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:02:55 by okraus            #+#    #+#             */
/*   Updated: 2023/01/26 17:10:51 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_print_string_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		i += write(fd, &s[i], 1);
	return (i);
}

int	ft_putstring_fd(char *s, int fd)
{
	int	i;

	i = 0;
	i = ft_print_string_fd(s, fd);
	return (i);
}
