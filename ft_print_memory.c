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
	write(fd, &"0123456789ABCDEF"[mem % 16], 1);
}

void	ft_putadd_fd(void *p, int fd)
{
	write(1, "0x", 2);
	ft_putmem_fd((uintptr_t)p, fd);
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

void	ft_variadic_test(char *s, ...)
{
	size_t	size;
	int		i;
	va_list ptr;

	size = ft_count_par(s);
	va_start(ptr, s);
	i = 0;
	while (s[i])
	{	
		if (s[i] == '%' && s[i + 1] != '%')
			{
				ft_putadd_fd(va_arg(ptr, void *), 1);
				i++;
			}
		if ((i == 0 && s[i] != '%') ||(i > 0 && s[i - 1] != '%'))
			write (1, &s[i], 1);
		i++;
	}
	va_end(ptr);
}

int	main(void)
{
	char	c;
	char	*p;

	c = 'a';
	p = &c;
	printf("print %p \n", (void *)&c);
	write(1, "write ", 6);
	ft_putadd_fd((void *)&c, 1);
	write(1, "\n", 1);
	ft_variadic_test("print %p \n", (void *)&c);
	
	return (0);
}
