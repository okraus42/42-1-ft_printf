/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:59:58 by okraus            #+#    #+#             */
/*   Updated: 2023/09/29 15:16:12 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_get_print_string(va_list arg, const char *s)
{
	char	*str;
	t_list	*lst;

	lst = ft_process_string(s);
	//create new list
	//fill list with arg stuff;
	//process list
	//join strings;
	return (str);
}

int	ft_printf(const char *s, ...)
{
	int		value;
	char	*str;
	va_list	arg;

	va_start(arg, s);
	str = ft_get_print_string(arg, s);
	va_end(arg);
	if (str)
	{
		value = write(1, str, ft_strlen(str));
		free(str);
	}
	else
		value = (-1);
	return (value);
}
