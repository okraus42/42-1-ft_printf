/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:02:50 by okraus            #+#    #+#             */
/*   Updated: 2023/01/27 17:06:15 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_unslen(unsigned int u)
{
	int	i;

	i = 0;
	if (u <= 0)
		i++;
	while (u)
	{
		u /= 10;
		i++;
	}
	return (i);
}

char	*ft_string_unsigned(unsigned int u)
{
	char			*str;
	int				i;

	i = ft_unslen(u) - 1;
	str = (char *)malloc((i + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[i + 1] = 0;
	while (u != 0)
	{
		str[i] = "0123456789"[u % 10];
		u = u / 10;
		i--;
	}
	return (str);
}

int	ft_print_unsigned_fd(unsigned int u, int fd)
{
	char	*s;
	int		i;

	s = ft_string_unsigned(u);
	i = 0;
	while (s[i])
	{
		i += write(fd, &s[i], 1);
	}
	return (i);
}

int	ft_putunsigned_fd(unsigned int u, int fd)
{
	int		i;

	i = 0;
	i = ft_print_unsigned_fd(u, fd);
	return (i);
}