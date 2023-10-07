/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:51:51 by okraus            #+#    #+#             */
/*   Updated: 2023/10/07 15:27:36 by okraus           ###   ########.fr       */
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
	if (ft_strlen(data->out) == data->field_width && data->flag & ZERO && data->out[0] == '0')
	{
		if (data->value.ll < 0)
			data->out[0] = '-';
		else if (data->flag & PLUS)
			data->out[0] = '+';
		else if (data->flag & SPACE)
			data->out[0] = ' ';
		if (!data->out)
			return (1);
	}
	else
	{
		if (data->value.ll < 0)
			data->out = ft_strjoin_freeright("-", data->out);
		else if (data->flag & PLUS)
			data->out = ft_strjoin_freeright("+", data->out);
		else if (data->flag & SPACE)
			data->out = ft_strjoin_freeright(" ", data->out);
		if (!data->out)
			return (1);
	}
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
			err = ft_padright(i, ' ', &data->out);
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

int	ft_process_prcint(t_pf_info *data)
{
	int	i;
	char *temp;
	//get number
	data->out = ft_ltoa_base(data->value.ll, BASE_CAP, 10);
	if(!data->out)
		return (1);
	if (data->out[0] == '-')//remove sign
	{
		temp = data->out;
		data->out = ft_strdup(&data->out[1]);
		free(temp);
		if(!data->out)
			return (1);
	}
	//process precision
	printf("RAW INT: %s\n", data->out); //remove later
	if (data->precision || (data->flag & ZERO && !(data->flag & 0x84))) //0x84 PERIOD & MINUS
	{
		i = data->precision - ft_strlen(data->out);
		if (!(data->flag & PERIOD))
			i = data->field_width - ft_strlen(data->out);
		if (i > 0)
			if (ft_padleft(i, '0', &data->out))
				return (1);
	}
	printf("PRECISION INT: %s\n", data->out); 
	//process + ' '
	if (ft_signed_flags(data))
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

int	ft_process_prc(t_pf_info *data)
{
	data->out = ft_strdup("%");
	data->outlen = 1;
	return (0);
}

int	ft_process_prcstr(t_pf_info *data)
{
	//process precision
	if (!data->value.s && data->precision >= 6U)
		data->out = ft_strdup("(null)");
	else if (!data->value.s)
		data->out = ft_strdup("");
	else if (data->flag & PERIOD)
		data->out = ft_string_copy_n(data->value.s, data->precision);
	else
		data->out = ft_stringcopy(data->value.s);
	if(!data->out)
		return (1);
	printf("RAW STR: %s\n", data->out); //remove later
	//process field width (if zero and no precision fill with zeros else fill with space) //check the - flag
	if (data->field_width > ft_strlen(data->out))
		if (ft_field_width(data))
			return (1);
	data->outlen = ft_strlen(data->out);
	printf("PROCESSED STR: %s\n", data->out); //remove later
	return (0);
}

int	ft_process_prcchr(t_pf_info *data)
{
	char s[2];

	s[0] = data->value.i;
	s[1] = 0;
	data->out = ft_strdup(s);
	if (!data->out)
		return (1);
	data->outlen = ft_strlen(data->out);
	return (0);
}

int	ft_process_percent(t_pf_info *data)
{
	int	err;

	err = 1;
	if (data->type_flag & SIGNED_INT)
		err = ft_process_prcint(data);
	if (data->type_flag & PERCENTAGE)
		err = ft_process_prc(data);
	if (data->type_flag & LOWERCASE_S)
		err = ft_process_prcstr(data);
	if (data->type_flag & LOWERCASE_C)
		err = ft_process_prcchr(data);
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
		printf("err = %i, str = %s\n", err, data->orig);
		lst = lst->next;
		
	}
	return (err);
}