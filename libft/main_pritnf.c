/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pritnf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:51:02 by okraus            #+#    #+#             */
/*   Updated: 2023/10/08 13:57:52 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/libft.h"

int	main(void)
{
	//ft_printf("abc%2s%cab%#012.5ic%%def", "xxx", 'c', 0x12345678);
	write(1, "\n", 1);
	ft_printf("%2s123%cab%+-020.15ic%%\n", "xxx", 'c', 0x12345678);
	ft_printf("123%iab%+-020.15hic%%\n", 'c', 0x12345678);
	ft_printf("123%ca%+05ib%+020.15ic%2.4sd%9.6se%-8.2sfghijkl%%\n", 'c', -1234, -0x12345678, "abcdef", (char *)NULL, "abcdef");
	printf("123%ca%+05ib%+020.15ic%2.4sd%9.6se%-8.2sfghijkl%%\n", 'c', -1234, -0x12345678, "abcdef", (char *)NULL, "abcdef");
	ft_printf("a%ob%uc%xd%Xe%lxf%#og%10xh%10.5xijkl\n", 42, 42, 42, 42, 9223372036854775808UL, 42, 42, 42);
	printf("a%ob%uc%xd%Xe%lxf%#og%10xh%10.5xijkl\n", 42, 42, 42, 42, 9223372036854775808UL, 42, 42, 42);
	
	ft_printf("%30p %20p\n", NULL, &"abcdef");
	printf("%30p %20p\n", NULL, &"abcdef");
	//printf("%lli %s %s\n", -9223372036854775807LL -1LL, ft_ltoa_base(-9223372036854775807LL -1LL, "0123456789abcdef", 10), ft_ultoa_base(0x1234567890fDECBA, "0123456789abcdef", 16));
	return (0);
}