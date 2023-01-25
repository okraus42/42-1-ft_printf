/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:49:23 by okraus            #+#    #+#             */
/*   Updated: 2023/01/22 14:22:58 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

void	ft_putmem_fd(uintptr_t mem, int fd)
{
	if (mem / 16)
		ft_putmem_fd(mem / 16, fd);
	write(fd, &"0123456789abcdef"[mem % 16], 1);
}


int	ft_putadd_fd(void *p, int fd)
{
	write(1, "0x", 2);
	ft_putmem_fd((uintptr_t)p, fd);
	return (2);
}

void	ft_putuns2_fd(unsigned int u, int fd)
{
	if (u / 10)
		ft_putuns2_fd(u / 10, fd);
	write(fd, &"0123456789"[u % 10], 1);
}

int	ft_putuns_fd(unsigned int u, int fd)
{
	ft_putuns2_fd(u, fd);
	return (2);
}

int	ft_count_par(char *s)
{
	int	i;
	int	par;

	i = 0;
	par = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] != '%')
			{
				par++;
				i++;
			}
		i++;
	}
	return (par);	
}

int	ft_put_percent(void)
{
	write (1, "%", 1);
	return (1);
}

int	ft_putstuff_test(va_list arg, char *s)
{
	int	i;

	i = 0;
	while (s[i] != 'c' && s[i] != 's' && s[i] != 'p' && s[i] != 'd'
		&& s[i] != 'i' && s[i] != 'u' && s[i] != 'x' && s[i] != 'X'
		&& s[i] != '\0')
	{
		//write (1, "$", 1);
		i++;
	}

	if (s[i] == 'p')
	{
		//write (1, "*", 1);
		return (ft_putadd_fd(va_arg(arg, void *), 1));
	}
	if (s[i] == 'u')
	{
		//write (1, "*", 1);
		return (ft_putuns_fd(va_arg(arg, unsigned int), 1));
	}
	return (0);
}


int	ft_printf_test(char *s, ...)
{
	size_t	size;
	int		i;
	va_list arg;

	size = ft_count_par(s);
	va_start(arg, s);
	i = 0;
	while (s[i])
	{	
		if (s[i] == '%')
		{
			if (s[i + 1] != '%')
			{
				i += ft_putstuff_test(arg, &s[i]);
			}
			else
			{
				write(1, &s[i], 1);
				i += 2;
			}
		}
		else
		{
			write (1, &s[i], 1);
			i++;
		}
	}
	va_end(arg);
	size = i;
	return (size);
}

int	main(void)
{
	char			c;
	char			d;
	unsigned int	u;

	c = 'a';
	d = 'b';
	u = 4123456789;
	printf("printf : -%p--%%--%p--%u-\n", (void *)&c, (void *)&d, u);
	write(1, "write ", 6);
	ft_putadd_fd((void *)&c, 1);
	write(1, "\n", 1);
	ft_printf_test("ftprint: -%p--%%--%p--%u-\n", (void *)&c, (void *)&d, u);
	
	return (0);
}
