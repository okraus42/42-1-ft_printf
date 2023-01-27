/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_hexabig.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:02:50 by okraus            #+#    #+#             */
/*   Updated: 2023/01/27 17:06:27 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hexlen(int h)
{
	int	i;

	i = 0;
	if (h <= 0)
		i++;
	while (h)
	{
		h /= 16;
		i++;
	}
	return (i);
}

char	*ft_string_hexabig(unsigned int h)
{
	char			*str;
	int				i;

	i = ft_hexlen(h) - 1;
	str = (char *)malloc((i + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[i + 1] = 0;
	if (h == 0)
		str[i] = '0';
	while (h != 0)
	{
		str[i] = "0123456789ABCDEF"[h % 16];
		h = h / 16;
		i--;
	}
	return (str);
}

int	ft_print_hexabig_fd(unsigned int h, int fd, t_output *t)
{
	char	*s;
	int		i;

	s = ft_string_hexabig(h);
	i = 0;
	if (t->hash)
		s = ft_strjoin("0X", s);
	while (s[i])
	{
		i += write(fd, &s[i], 1);
	}
	return (i);
}

int	ft_puthexabig_fd(unsigned int h, int fd, t_output *t)
{
	int		i;

	i = 0;
	i = ft_print_hexabig_fd(h, fd, t);
	return (i);
}