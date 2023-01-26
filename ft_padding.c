/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:14:02 by okraus            #+#    #+#             */
/*   Updated: 2023/01/26 18:25:15 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_padint(char *s, t_output *t)
{
	if (t->padsize && !t->zero)
	{
		while ((int)ft_strlen(s) < t->padsize)
		{
			s = ft_strjoin(" ", s);
		}
	}
	return (s);
}

char	*ft_precint(char *s, t_output *t)
{
	int	sign;

	sign = 0;
	if (s[0] == '-')
	{
		sign = -1;
		s++;
	}
	while ((int)ft_strlen(s) < t->precision
		|| (t->zero && (int)ft_strlen(s) < t->padsize))
	{
		s = ft_strjoin("0", s);
	}
	if (sign == -1)
		s = ft_strjoin("-", s);
	return (s);
}
