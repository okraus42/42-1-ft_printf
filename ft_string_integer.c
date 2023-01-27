/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_integer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:02:50 by okraus            #+#    #+#             */
/*   Updated: 2023/01/27 17:06:19 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_intlen(int d)
{
	int	i;

	i = 0;
	if (d <= 0)
		i++;
	while (d)
	{
		d /= 10;
		i++;
	}
	return (i);
}

char	*ft_string_integer(int d)
{
	char			*str;
	int				i;
	unsigned int	m;

	i = ft_intlen(d) - 1;
	str = (char *)malloc((i + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[i + 1] = 0;
	if (d == 0)
		str[i] = '0';
	if (d < 0)
	{
		str[0] = '-';
		m = -d;
	}
	else
		m = d;
	while (m != 0)
	{
		str[i] = "0123456789"[m % 10];
		m = m / 10;
		i--;
	}
	return (str);
}

int	ft_print_integer_fd(int d, int fd, t_output	*t)
{
	char	*s;
	int		i;

	s = ft_string_integer(d);
	i = 0;
	if (t->precision || (t->padsize && t->zero))
	{
		s = ft_precint(s, t);
	}
	if (t->plus && d >= 0)
		s = ft_strjoin("+", s);
	else if (t->space && d >= 0)
		s = ft_strjoin(" ", s);
	if (t->padsize)
		s = ft_padint(s, t);
	while (s[i])
	{
		i += write(fd, &s[i], 1);
	}
	return (i);
}

int	ft_putinteger_fd(int d, int fd, t_output *t)
{
	int		i;

	i = 0;
	i = ft_print_integer_fd(d, fd, t);
	return (i);
}
