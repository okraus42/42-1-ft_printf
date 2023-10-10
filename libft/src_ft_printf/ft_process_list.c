/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:51:51 by okraus            #+#    #+#             */
/*   Updated: 2023/10/10 15:45:52 by okraus           ###   ########.fr       */
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
	*s = ft_strjoin_freeboth(str, *s);
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
	*s = ft_strjoin_freeboth(*s, str);
	if (!*s)
		return (1);
	return (0);
}

int	ft_signed_flags(t_pf_info *data)
{
	if (ft_strlen(data->out) == data->field_width
		&& data->flag & ZERO && data->out[0] == '0')
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

//	0x84 PERIOD & MINUS
int	ft_process_prcint(t_pf_info *data)
{
	int		i;
	char	*temp;

	data->out = ft_ltoa_base(data->value.ll, BASE_CAP, 10);
	if (!data->out)
		return (1);
	if (data->out[0] == '-')
	{
		temp = data->out;
		data->out = ft_strdup(&data->out[1]);
		free(temp);
		if(!data->out)
			return (1);
	}
	if (data->precision || (data->flag & ZERO && !(data->flag & 0x84)))
	{
		i = data->precision - ft_strlen(data->out);
		if (!(data->flag & PERIOD))
			i = data->field_width - ft_strlen(data->out);
		if (i > 0)
			if (ft_padleft(i, '0', &data->out))
				return (1);
	}
	if (ft_signed_flags(data))
		return (1);
	if (data->field_width > ft_strlen(data->out))
		if (ft_field_width(data))
			return (1);
	data->outlen = ft_strlen(data->out);
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
	if (data->field_width > ft_strlen(data->out))
		if (ft_field_width(data))
			return (1);
	data->outlen = ft_strlen(data->out);
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

int	ft_unsigned_flags(t_pf_info *data)
{
	if (data->flag & HASHTAG || data->type_flag & LOWERCASE_P)
	{
		if (data->type_flag & LOWERCASE_O)
			data->out = ft_strjoin_freeright("0", data->out);
		else if (data->type_flag & 0x1001000) //x or p
		{
			data->out = ft_strjoin_freeright("0x", data->out);
		}
		else if (data->type_flag & UPPERCASE_X)
			data->out = ft_strjoin_freeright("0X", data->out);
		if (!data->out)
			return (1);
	}
	return (0);
}

//	0x84 PERIOD & MINUS
int	ft_process_prcu(t_pf_info *data)
{
	int	i;

	data->out = ft_ultoa_base(data->value.ull, BASE_CAP, 10);
	if(!data->out)
		return (1);
	if (data->precision || (data->flag & ZERO && !(data->flag & 0x84)))
	{
		i = data->precision - ft_strlen(data->out);
		if (!(data->flag & PERIOD))
			i = data->field_width - ft_strlen(data->out);
		if (i > 0)
			if (ft_padleft(i, '0', &data->out))
				return (1);
	}
	if (ft_unsigned_flags(data))
		return (1);
	if (data->field_width > ft_strlen(data->out))
		if (ft_field_width(data))
			return (1);
	data->outlen = ft_strlen(data->out);
	return (0);
}

//	0x84 PERIOD & MINUS
int	ft_process_prco(t_pf_info *data)
{
	int	i;

	data->out = ft_ultoa_base(data->value.ull, BASE_CAP, 8);
	if(!data->out)
		return (1);
	if (data->precision || (data->flag & ZERO && !(data->flag & 0x84))) 
	{
		i = data->precision - ft_strlen(data->out);
		if (!(data->flag & PERIOD))
			i = data->field_width - ft_strlen(data->out);
		if (i > 0)
			if (ft_padleft(i, '0', &data->out))
				return (1);
	}
	if (ft_unsigned_flags(data))
		return (1);
	if (data->field_width > ft_strlen(data->out))
		if (ft_field_width(data))
			return (1);
	data->outlen = ft_strlen(data->out);
	return (0);
}

//	0x84 PERIOD & MINUS
int	ft_process_prcx(t_pf_info *data)
{
	int	i;

	data->out = ft_ultoa_base(data->value.ull, BASE_SML, 16);
	if(!data->out)
		return (1);
	if (data->precision || (data->flag & ZERO && !(data->flag & 0x84)))
	{
		i = data->precision - ft_strlen(data->out);
		if (!(data->flag & PERIOD))
			i = data->field_width - ft_strlen(data->out);
		if (i > 0)
			if (ft_padleft(i, '0', &data->out))
				return (1);
	}
	if (ft_unsigned_flags(data))
		return (1);
	if (data->field_width > ft_strlen(data->out))
		if (ft_field_width(data))
			return (1);
	data->outlen = ft_strlen(data->out);
	return (0);
}

//	0x84 PERIOD & MINUS
int	ft_process_prcx2(t_pf_info *data)
{
	int	i;

	data->out = ft_ultoa_base(data->value.ull, BASE_CAP, 16);
	if(!data->out)
		return (1);
	if (data->precision || (data->flag & ZERO && !(data->flag & 0x84)))
	{
		i = data->precision - ft_strlen(data->out);
		if (!(data->flag & PERIOD))
			i = data->field_width - ft_strlen(data->out);
		if (i > 0)
			if (ft_padleft(i, '0', &data->out))
				return (1);
	}
	if (ft_unsigned_flags(data))
		return (1);
	if (data->field_width > ft_strlen(data->out))
		if (ft_field_width(data))
			return (1);
	data->outlen = ft_strlen(data->out);
	return (0);
}

int	ft_process_prcuns(t_pf_info *data)
{
	if (data->type_flag & LOWERCASE_O && ft_process_prco(data))
		return (1);
	else if (data->type_flag & LOWERCASE_U && ft_process_prcu(data))
		return (1);
	else if (data->type_flag & LOWERCASE_X && ft_process_prcx(data))
		return (1);
	else if (data->type_flag & UPPERCASE_X && ft_process_prcx2(data))
		return (1);
	if(!data->out)
		return (1);
	return (0);
}

int	ft_process_prcptr(t_pf_info *data)
{
	if (!data->value.p)
		data->out = ft_strdup("(nil)");
	else
		data->out = ft_ultoa_base((unsigned long long)data->value.p, BASE_SML, 16);
	if(!data->out)
		return (1);
	if (data->value.p && ft_unsigned_flags(data))
		return (1);
	if (data->field_width > ft_strlen(data->out))
		if (ft_field_width(data))
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
	if (data->type_flag & CONVERSION_UNSIGNED)
		err = ft_process_prcuns(data);
	if (data->type_flag & PERCENTAGE)
		err = ft_process_prc(data);
	if (data->type_flag & LOWERCASE_S)
		err = ft_process_prcstr(data);
	if (data->type_flag & LOWERCASE_C)
		err = ft_process_prcchr(data);
	if (data->type_flag & LOWERCASE_P)
		err = ft_process_prcptr(data);
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
	int			err;
	t_pf_info	*data;

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
