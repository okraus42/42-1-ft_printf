/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:51:51 by okraus            #+#    #+#             */
/*   Updated: 2023/10/03 12:18:51 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	ft_process_int(t_pf_info *data)
{
	//get number
	//process flags
}

int	ft_process_percent(t_pf_info *data)
{
	int	err;

	err = 1;
	if (data->type_flag & SIGNED_INT)
		err = ft_process_int(data);
	return (err);
}

int	ft_process_string(t_pf_info *data)
{
	int	len;

	len = 0;
	while (data->orig[len] && data->orig[len] != '%')
		len++;
	data->outlen = len;
	data->out = malloc(len + 1);
	if (!data->out)
		return (1);
	len = 0;
	while (data->orig[len] && data->orig[len] != '%')
	{
		data->out[len] = data->orig[len];
		len++;
	}
	data->out[len] = 0;
	return (0);
}

int	ft_process_list(t_list *lst)
{
	t_pf_info	*data;
	int			err;

	err = 0;
	while (lst)
	{
		data = lst->content;
		if (data->type)
			err = ft_process_percent(data);
		else
			err = ft_process_string(data);
		lst = lst->next;
	}
}