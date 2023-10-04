/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_strings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:22:52 by okraus            #+#    #+#             */
/*   Updated: 2023/10/04 14:45:38 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_print_lst_to_strinf(t_list *lst)
{
	t_pf_info	*data;
	char		*str;

	str = NULL;
	while (lst)
	{
		data = lst->content;
		if (!str)
		{
			if (data->out)
				str = ft_strdup(data->out);
		}
		else
			if (data->out)
				str = ft_strjoin_freeleft(str, data->out);
		lst = lst->next;
	}
	return (str);
}
