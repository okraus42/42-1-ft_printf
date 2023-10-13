/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:59:58 by okraus            #+#    #+#             */
/*   Updated: 2023/10/13 15:40:48 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void	ft_print_list(t_list *lst)
{
	t_pf_info	*data;

	while (lst)
	{
		data = lst->content;
		if (data)
		{
			if (data->orig)
			{
				printf("string: %s\n", data->orig);
			}
			else
				write(1, "string not found", 16);
			printf("data type: %i\n", data->type);
			printf("flag: %x\n", data->flag);
			printf("value_flag: %x\n", data->value_flag);
			printf("type_flag: %x\n", data->type_flag);
			printf("value: %i\n", data->value.i);
			printf("width: %x\n", data->field_width);
			printf("precision: %x\n", data->precision);
		}
		else
			write(1, "data not found\n", 15);
		lst = lst->next;
	}
}

int	ft_add_node(t_list **head, const char *s, int type, int *end)
{
	t_list		*lst;
	t_pf_info	*data;

	data = ft_calloc(sizeof(t_pf_info), 1);
	if (!data)
		return (1);
	data->orig = s;
	data->type = type & 1;
	*end = type;
	lst = ft_lstnew(data);
	if (!lst)
	{
		free(data);
		return (1);
	}
	ft_lstadd_back(head, lst);
	return (0);
}

t_list	*ft_process_input_string(const char *s)
{
	int		i;
	int		error;
	int		end;
	t_list	*head;

	i = 0;
	end = 2;
	head = NULL;
	error = 0;
	while (s[i] && !error)
	{
		if (end & 1 && ft_strchr(F_TYPES, s[i]))
			end = 2;
		else if (s[i] == '%')
			error = ft_add_node(&head, &s[i], 1, &end);
		else if (end & 2)
			error = ft_add_node(&head, &s[i], 0, &end);
		++i;
	}
	if (error)
		return(NULL); //free head
	return (head);
}

void	ft_init_flags_helper(int flag, t_pf_info *data)
{
	data->flag |= flag;
}

void	ft_init_flags(int *i, t_pf_info *data)
{
	while (data->orig[*i] && ft_strchr(F_FLAGS, data->orig[*i]))
	{
		if (data->orig[*i] == '0')
			ft_init_flags_helper(ZERO, data);
		else if (data->orig[*i] == '#')
			ft_init_flags_helper(HASHTAG, data);
		else if (data->orig[*i] == '-')
			ft_init_flags_helper(MINUS, data);
		else if (data->orig[*i] == '+')
			ft_init_flags_helper(PLUS, data);
		else if (data->orig[*i] == ' ')
			ft_init_flags_helper(SPACE, data);
		else if (data->orig[*i] == '\'')
			ft_init_flags_helper(APOSTROPHE, data);
		else if (data->orig[*i] == 'I')
			ft_init_flags_helper(UPPERCASE_I, data);
		++(*i);
	}
}

void	ft_init_field_width(int *i, int *err, t_pf_info *data, va_list arg)
{
	int			n;
	long long	num;

	if (data->orig[*i] == '*')
	{
		data->field_width = va_arg(arg, unsigned int);
		++(*i);
	}
	else
	{
		n = 0;
		num = ft_latoi(&data->orig[*i]);
		while (ft_isdigit(data->orig[*i]))
		{
			++n;
			++(*i);
		}
		if (n > 15 || num > 0xFFFFFFFF)
			*err = 1;
		else
			data->field_width = (unsigned int)num;
		if (*err) //REMOVE LATER
			printf("ERR WIDTH: %s\n", data->orig); //REMOVE LATER
	}
}

void	ft_init_precision(int *i, int *err, t_pf_info *data, va_list arg)
{
	int			n;
	long long	num;

	data->flag |= PERIOD;
	if (data->orig[*i] == '*')
	{
		data->precision = va_arg(arg, unsigned int);
		++(*i);
	}
	else
	{
		n = 0;
		num = ft_latoi(&data->orig[*i]);
		while (ft_isdigit(data->orig[*i]))
		{
			++n;
			++(*i);
		}
		if (n > 15 || num > 0xFFFFFFFF)
			*err = 1;
		else if (num > 0)
			data->precision = (unsigned int)num;
		else
			data->precision = 0;
	}
	if (*err)//REMOVE LATER
		printf("ERR PRECISION: %s\n", data->orig); //REMOVE later
}

void	ft_init_modifiers(int *i, t_pf_info *data)
{
	if (data->orig[*i] == 'h' && data->orig[(*i) + 1] == 'h')
	{
		data->type_flag |= LOWERCASE_HH;
		++(*i);
	}
	else if (data->orig[*i] == 'l' && data->orig[(*i) + 1] == 'l')
	{
		data->type_flag |= LOWERCASE_LL;
		++(*i);
	}
	else if (data->orig[*i] == 'h')
		data->type_flag |= LOWERCASE_H;
	else if (data->orig[*i] == 'l')
		data->type_flag |= LOWERCASE_L;
	else if (data->orig[*i] == 'z')
		data->type_flag |= LOWERCASE_Z;
	else if (data->orig[*i] == 'j')
		data->type_flag |= LOWERCASE_J;
	else if (data->orig[*i] == 't')
		data->type_flag |= LOWERCASE_T;
	++(*i);
}

//maybe typecast everything toll?
//char and short promoted to int
void ft_get_int_value_helper(t_pf_info *data, va_list arg, int flag)
{
	data->value_flag = flag;
	if (flag & SIGNED_CHAR)
		data->value.ll = (long long)va_arg(arg, int);
	else if (flag & SIGNED_SHORT)
		data->value.ll = (long long)va_arg(arg, int);
	else if (flag & LONG)
		data->value.ll = (long long)va_arg(arg, long);
	else if (flag & LONG_LONG)
		data->value.ll = (long long)va_arg(arg, long long);
	else if (flag & INT)
		data->value.ll = (long long)va_arg(arg, int);
}

int	ft_get_int_value(t_pf_info *data, va_list arg)
{
	if (data->type_flag & LENGTH_MODIFIER)
	{
		if (data->type_flag & LOWERCASE_HH)
			ft_get_int_value_helper(data, arg, SIGNED_CHAR);
		else if (data->type_flag & LOWERCASE_H)
			ft_get_int_value_helper(data, arg, SIGNED_SHORT); 
		else if (data->type_flag & LOWERCASE_L)
			ft_get_int_value_helper(data, arg, LONG);
		else if (data->type_flag & LLL)
			ft_get_int_value_helper(data, arg, LONG_LONG);
		else
			return (1);
	}
	else
		ft_get_int_value_helper(data, arg, INT);
	return (0);
}

int	ft_init_int(char c, t_pf_info *data, va_list arg)
{
	if (c == 'c')
		data->type_flag |= LOWERCASE_C;
	else if (c == 'd')
		data->type_flag |= LOWERCASE_D;
	else if (c == 'i')
		data->type_flag |= LOWERCASE_I;
	return (ft_get_int_value(data, arg));
}

//maybe typecast everything to ull?
//unsigned char and unsigned short promoted to unsigned int
void ft_get_unsigned_int_value_helper(t_pf_info *data, va_list arg, int flag)
{
	data->value_flag = flag;
	if (flag & UNSIGNED_CHAR)
		data->value.ull = va_arg(arg, unsigned int);
	else if (flag & UNSIGNED_SHORT)
		data->value.ull = va_arg(arg, unsigned int);
	else if (flag & UNSIGNED_LONG)
		data->value.ull = va_arg(arg, unsigned long);
	else if (flag & UNSIGNED_LONG_LONG)
		data->value.ull = va_arg(arg, unsigned long long);
	else if (flag & SIZE_T)
		data->value.ull = va_arg(arg, size_t);
	else if (flag & UNSIGNED_INT)
		data->value.ull = va_arg(arg, unsigned int);
}

int	ft_get_unsigned_int_value(t_pf_info *data, va_list arg)
{
	if (data->type_flag & LENGTH_MODIFIER)
	{
		if (data->type_flag & LOWERCASE_HH)
			ft_get_unsigned_int_value_helper(data, arg, UNSIGNED_CHAR);
		else if (data->type_flag & LOWERCASE_H)
			ft_get_unsigned_int_value_helper(data, arg, UNSIGNED_SHORT);
		else if (data->type_flag & LOWERCASE_L)
			ft_get_unsigned_int_value_helper(data, arg, UNSIGNED_LONG);
		else if (data->type_flag & LLL)
			ft_get_unsigned_int_value_helper(data, arg, UNSIGNED_LONG_LONG);
		else if (data->type_flag & LOWERCASE_Z)
			ft_get_unsigned_int_value_helper(data, arg, SIZE_T);
		else
			return (1);
	}
	else
		ft_get_unsigned_int_value_helper(data, arg, UNSIGNED_INT);
	return (0);
}

int	ft_init_unsigned(char c, t_pf_info *data, va_list arg)
{
	if (c == 'o')
		data->type_flag |= LOWERCASE_O;
	else if (c == 'u')
		data->type_flag |= LOWERCASE_U;
	else if (c == 'x')
		data->type_flag |= LOWERCASE_X;
	else if (c == 'X')
		data->type_flag |= UPPERCASE_X;
	else if (c == 'b')
		data->type_flag |= LOWERCASE_B;
	else if (c == 'B')
		data->type_flag |= UPPERCASE_B;
	return (ft_get_unsigned_int_value(data, arg));
}

//float promoted to double
int	ft_get_double_value(t_pf_info *data, va_list arg)
{
	if (data->type_flag & LENGTH_MODIFIER)
	{
		if (data->type_flag & LLL)
		{
			data->value_flag = LONG_DOUBLE;
			data->value.ld = va_arg(arg, long double);
		}
		else if (data->type_flag & LOWERCASE_L)
		{
			data->value_flag = DOUBLE;
			data->value.d = va_arg(arg, double);
		}
		else
			return (1);
	}
	else
	{
		data->value_flag = DOUBLE;
		data->value.d = va_arg(arg, double);
	}
	return (0);
}

int	ft_init_double(char c, t_pf_info *data, va_list arg)
{
	if (c == 'e')
		data->type_flag |= LOWERCASE_E;
	else if (c == 'E')
		data->type_flag |= UPPERCASE_E;
	else if (c == 'f')
		data->type_flag |= LOWERCASE_F;
	else if (c == 'F')
		data->type_flag |= UPPERCASE_F;
	else if (c == 'g')
		data->type_flag |= LOWERCASE_G;
	else if (c == 'G')
		data->type_flag |= UPPERCASE_G;
	else if (c == 'a')
		data->type_flag |= LOWERCASE_A;
	else if (c == 'A')
		data->type_flag |= UPPERCASE_A;
	return (ft_get_double_value(data, arg));
}

int	ft_init_pointer(char c, t_pf_info *data, va_list arg)
{
	if (data->type_flag & LENGTH_MODIFIER)
		return (1);
	if (c == 's')
	{
		data->type_flag |= LOWERCASE_S;
		data->value_flag = CHAR_POINTER;
		data->value.s = va_arg(arg, char *);
	}
	else if (c == 'p')
	{
		data->type_flag |= LOWERCASE_P;
		data->value_flag = VOID_POINTER;
		data->value.p = va_arg(arg, void *);
	}
	return (0);
}

int	ft_init_conversion(int i, t_pf_info *data, va_list arg)
{
	char	c;
	int		err;

	c = data->orig[i];
	err = 0;
	if (c == 'i' || c == 'd' || c == 'c')
		err = ft_init_int(c, data, arg);
	else if (c == 'o' || c == 'u' || c == 'x' || c == 'X'
		|| c == 'b' || c == 'B')
		err = ft_init_unsigned(c, data, arg);
	else if (c == 'e' || c == 'E' || c == 'f' || c == 'F'
		|| c == 'g' || c == 'G' || c == 'a' || c == 'A')
		err = ft_init_double(c, data, arg);
	else if (data->orig[i] == 's' || data->orig[i] == 'p')
		err = ft_init_pointer(c, data, arg);
	else if (data->orig[i] == 'C')
		data->type_flag |= UPPERCASE_C;
	else if (data->orig[i] == 'P')
		data->type_flag |= UPPERCASE_P;
	else if (data->orig[i] == '%')
		data->type_flag |= PERCENTAGE;
	else
		err = 1;
	if (err)				//REMOVE LATER
		printf("ERR CONVERSION: %s\n", data->orig); //REMOVE LATER
	return (err);
}

int	ft_init_list(va_list arg, t_list *lst)
{
	t_pf_info	*data;
	int			i;
	int			err;

	
	err = 0;
	while (lst)
	{
		data = lst->content;
		i = 1;
		if (data->type)
		{
			if (data->orig[i] && ft_strchr(F_FLAGS, data->orig[i]))
				ft_init_flags(&i, data);
			if (data->orig[i] && ft_strchr(F_NUMBERS, data->orig[i]))
				ft_init_field_width(&i, &err, data, arg);
			if (data->orig[i] == '.')
			{
				i++;
				ft_init_precision(&i, &err, data, arg);
			}
			if (data->orig[i] && ft_strchr(F_MODIFIER, data->orig[i]))
				ft_init_modifiers(&i, data);
			if (err || !ft_strchr(F_TYPES, data->orig[i]))
			{
				if (!err)
					printf ("ERROR TYPES %s\n", &data->orig[i]);
				else
					printf ("ERROR ERR\n");
				return (1);
			}
			if (ft_init_conversion(i, data, arg))
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

char	*ft_get_print_string(va_list arg, const char *s, int *len)
{
	char	*str;
	t_list	*lst;

	lst = ft_process_input_string(s);
	str = NULL;
	if (ft_init_list(arg, lst))
	{
		ft_lstclear(&lst, ft_clear_pf_data);
		lst = NULL;
	}
	if (ft_process_list(lst))
	{
		ft_lstclear(&lst, ft_clear_pf_data);
		lst = NULL;
	}
	str = ft_print_lst_to_string(lst, len);
	// if (lst)
	// 	ft_print_list(lst); 
	if (lst)
		ft_lstclear(&lst, ft_clear_pf_data);
	return (str);
}

int	ft_printf(const char *s, ...)
{
	int		value;
	char	*str;
	int		len;
	va_list	arg;

	len = 0;
	va_start(arg, s);
	str = ft_get_print_string(arg, s, &len);
	va_end(arg);
	if (str)
	{
		value = write(1, str, len);
		free(str);
	}
	else
		value = (-1);
	return (value);
}
