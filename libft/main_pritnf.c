/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pritnf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:51:02 by okraus            #+#    #+#             */
/*   Updated: 2023/10/07 15:28:33 by okraus           ###   ########.fr       */
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

	//printf("%lli %s %s\n", -9223372036854775807LL -1LL, ft_ltoa_base(-9223372036854775807LL -1LL, "0123456789abcdef", 10), ft_ultoa_base(0x1234567890fDECBA, "0123456789abcdef", 16));
	return (0);
}