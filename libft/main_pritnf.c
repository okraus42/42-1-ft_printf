/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pritnf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:51:02 by okraus            #+#    #+#             */
/*   Updated: 2023/10/06 17:11:51 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/libft.h"

int	main(void)
{
	//ft_printf("abc%2s%cab%#012.5ic%%def", "xxx", 'c', 0x12345678);
	write(1, "\n", 1);
	ft_printf("%2s123%cab%+-020.15ic%%\n", "xxx", 'c', 0x12345678);
	ft_printf("123%iab%+-020.15hic%%\n", 'c', 0x12345678);
	ft_printf("123%iab%+020.15hic%2.4sd%9.6se%-08.2sf%%\n", 'c', 0x12345678, "abcdef", (char *)NULL, "abcdef");
	return (0);
}