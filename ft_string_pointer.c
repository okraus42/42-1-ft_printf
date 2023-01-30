/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:02:50 by okraus            #+#    #+#             */
/*   Updated: 2023/01/28 11:03:23 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_memlen(uintptr_t m)
{
	int	i;

	i = 0;
	if (m <= 0)
		i++;
	while (m)
	{
		m /= 16;
		i++;
	}
	return (i);
}

char	*ft_string_pointer(void *mem)
{
	char			*str;
	int				i;
	uintptr_t		m;

	m = (uintptr_t)mem;
	i = ft_memlen(m) - 1;
	str = (char *)malloc((i + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[i + 1] = 0;
	while (m != 0)
	{
		str[i] = "0123456789abcdef"[m % 16];
		m = m / 16;
		i--;
	}
	return (str);
}

int	ft_print_pointer_fd(void *mem, int fd)
{
	char	*s;
	int		i;

	s = ft_string_pointer(mem);
	i = 0;
	if (mem == NULL)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	write(fd, "0x", 2);
	while (s[i])
	{
		i += write(fd, &s[i], 1);
	}
	free(s);
	return (i + 2);
}

int	ft_putpointer_fd(void *mem, int fd)
{
	int		i;

	i = 0;
	i = ft_print_pointer_fd(mem, fd);
	return (i + 2);
}
