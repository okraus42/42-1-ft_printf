/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:49:23 by okraus            #+#    #+#             */
/*   Updated: 2023/01/26 18:13:10 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putstuff(va_list arg, char *s, int *q, t_output	*t)
{
	ft_prefill_struct(t, &s[q[0]]);
	while (s[q[0]] != 'c' && s[q[0]] != 's' && s[q[0]] != 'p' && s[q[0]] != 'd'
		&& s[q[0]] != 'i' && s[q[0]] != 'u' && s[q[0]] != 'x' && s[q[0]] != 'X'
		&& s[q[0]] != '%' && s[q[0]] != '\0')
		q[0]++;
	if (s[q[0]] == '%')
		q[1] += write(1, &s[q[0]], 1);
	else if (s[q[0]] == 'p')
		q[1] += ft_print_pointer_fd(va_arg(arg, void *), 1);
	else if (s[q[0]] == 'u')
		q[1] += ft_putunsigned_fd(va_arg(arg, unsigned int), 1);
	else if (s[q[0]] == 'c')
		q[1] += ft_putchar_fd(va_arg(arg, int), 1);
	else if (s[q[0]] == 's')
		q[1] += ft_putstring_fd(va_arg(arg, char *), 1);
	else if (s[q[0]] == 'd' || s[q[0]] == 'i')
		q[1] += ft_putinteger_fd(va_arg(arg, int), 1, t);
	else if (s[q[0]] == 'X')
		q[1] += ft_puthexabig_fd(va_arg(arg, unsigned int), 1, t);
	else if (s[q[0]] == 'x')
		q[1] += ft_puthexasmall_fd(va_arg(arg, unsigned int), 1, t);
	q[0]++;
}

int	ft_printf(char *s, ...)
{
	static int		q[2];
	va_list			arg;
	static t_output	*t;

	t = (t_output *)malloc(sizeof(t_output));
	if (!t)
		return (-1);
	va_start(arg, s);
	q[0] = 0;
	q[1] = 0;
	while (s[q[0]])
	{	
		if (s[q[0]] == '%')
		{
			ft_initialise_struct(t);
			q[0]++;
			ft_putstuff(arg, s, q, t);
		}
		else
		{
			q[1] += write (1, &s[q[0]], 1);
			q[0]++;
		}
	}
	va_end(arg);
	return (q[1]);
}

int	main(void)
{
	char			c;
	char			d;
	unsigned int	u;
	int				pf;
	int				fp;
	int				num;
	char			*s = "@@@";

	c = 'a';
	d = 'b';
	num = 2147483647;
	u = 4123456789;
	pf = printf("printf : a%pbc%%de%cfg%uhij%sk%+20.15dlm% inop%#Xq%xr\n", (void *)&c, d, u, s, num, 0, u, 42);
	fp = ft_printf("ftprint: a%pbc%%de%cfg%uhij%sk%+20.15dlm% inop%#Xq%xr\n", (void *)&c, d, u, s, num, 0, u, 42);
	printf ("pf = %d, fp = %d\n", pf, fp);
	return (0);
}
