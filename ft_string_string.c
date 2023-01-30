/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:02:55 by okraus            #+#    #+#             */
/*   Updated: 2023/01/30 15:49:13 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char_fd(char c, int fd, t_output *t)
{
	int		i;
	char	*s;

	i = 0;
	s = malloc(2 * sizeof(char));
	s[0] = c;
	s[1] = 0;
	if (t->padsize)
		s = ft_padint(s, t);
	while (s[i])
	{
		i += write(fd, &s[i], 1);
	}
	free(s);
	return (i);
}

int	ft_putchar_fd(char c, int fd, t_output *t)
{
	int	i;

	i = 0;
	i = ft_print_char_fd(c, fd, t);
	return (i);
}

int	ft_print_string_fd(char *s, int fd, t_output *t)
{
	int	i;

	i = 0;
	if (s == NULL && (!t->period || t->precision > 5))
	{
		write(fd, "(null)", 6);
		return (6);
	}
	else if (s == NULL)
		return (0);
	while (s[i] && (!t->period || i < t->precision))
		i += write(fd, &s[i], 1);
	return (i);
}

int	ft_putstring_fd(char *s, int fd, t_output *t)
{
	int	i;

	i = 0;
	i = ft_print_string_fd(s, fd, t);
	return (i);
}
