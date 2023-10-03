/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:51:51 by okraus            #+#    #+#             */
/*   Updated: 2023/10/03 17:38:20 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	ft_padleft(int i, char c, char **s)
{
	char	*str;

	str = malloc(i + 1);
	if (!str)
		return (1);
	str[i] = 0;
	str = ft_memset(str, c, i);
	str[i] = 0;
	printf("PADLEFT: %s\n", str);
	printf("PADLEFT: %s\n", *s);
	*s = ft_strjoin_freeboth(str, *s);
	printf("PADLEFT: %s\n", *s);
	if (!*s)
		return (1);
	return (0);
}

int	ft_padright(int i, char c, char **s)
{
	char	*str;

	str = malloc(i + 1);
	if (!str)
		return (1);
	str[i] = 0;
	str = ft_memset(str, c, i);
	str[i] = 0;
	printf("PADRIGHT: %s\n", str);
	printf("PADRIGHT: %s\n", *s);
	*s = ft_strjoin_freeboth(*s, str);
	printf("PADRIGHT: %s\n", *s);
	if (!*s)
		return (1);
	return (0);
}

int	ft_signed_flags(t_pf_info *data)
{
	if (data->flag & PLUS)
		data->out = ft_strjoin_freeright("+", data->out);
	else if (data->flag & SPACE)
		data->out = ft_strjoin_freeright(" ", data->out);
	if (!data->out)
		return (1);
	return (0);
}

int	ft_field_width(t_pf_info *data)
{
	int	i;
	int	err;

	i = data->field_width - ft_strlen(data->out);
	err = 0;
	if (data->flag & ZERO && !(data->flag & PERIOD))
	{
		if (data->flag & MINUS)
			err = ft_padright(i, '0', &data->out);
		else
			err = ft_padleft(i, '0', &data->out);
	}
	else
	{
		if (data->flag & MINUS)
			err = ft_padright(i, ' ', &data->out);
		else
			err = ft_padleft(i, ' ', &data->out);
	}
	return (err);
}

int	ft_process_int(t_pf_info *data)
{
	int	i;
	//get number
	data->out = ft_itoa(data->value.i);
	if(!data->out)
		return (1);
	//process precision
	printf("RAW INT: %s\n", data->out); //remove later
	if (data->precision)
	{
		i = data->precision - ft_strlen(data->out);
		if (i > 0)
			if (ft_padleft(i, '0', &data->out))
				return (1);
	}
	printf("PRECISION INT: %s\n", data->out); 
	//process + ' '
	if (data->value.i >= 0 && ft_signed_flags(data))
		return (1);
	printf("FLAG INT: %s\n", data->out); 
	//process field width (if zero and no precision fill with zeros else fill with space) //check the - flag
	if (data->field_width > ft_strlen(data->out))
		if (ft_field_width(data))
			return (1);
	data->outlen = ft_strlen(data->out);
	printf("PROCESSED INT: %s\n", data->out); //remove later
	return (0);
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
	printf("PROCESSED BASIC STR: %s\n", data->out); //remove later
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
	return (err);
}