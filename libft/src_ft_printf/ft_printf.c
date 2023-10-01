/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:59:58 by okraus            #+#    #+#             */
/*   Updated: 2023/10/01 17:26:56 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void ft_print_list(t_list *lst)
{
	t_pf_info	*data;
	while (lst)
	{
		data = lst->content;
		if (data)
		{
			if (data->orig)
			{
				write(1, "string: ", 8);
				write(1, data->orig, 1);
				write(1, " | ", 3);
			}
			else
				write(1, "string not found | ", 19);
			if (data->type)
			{
				write(1, "type of 1\n", 10);
			}
			else
				write(1, "type not found\n", 15);
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

t_list	*ft_process_string(const char *s)
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

// "0#-+ 'I"
// typedef enum e_print_flag
// {
// 	ZERO = 0x1,						// The value should be zero padded.  For d, i, o, u, x, X, a, A, e, E, f, F, g, and G conversions, the converted value is padded on the left with zeros rather than blanks.  If the 0 and - flags both appear, the 0 flag is ignored.  If a precision is given with an integer conversion (d, i, o, u, x, and X), the 0 flag is ignored.
// 	HASHTAG = 0x2,					// The value should be converted to an "alternate form".  For o conversions, the first character of the output string is made zero (by prefixing a 0 if it was not zero already). For x and X conversions, a nonzero result has the string "0x" (or "0X" for X conversions) prepended to it.  For a, A, e, E, f, F, g, and G conversions, the result will always contain a decimal point, even if no digits follow it (normally, a decimal point appears in the results of those conversions only if a digit follows).  For g and G conversions, trailing zeros are not removed from the result as they would otherwise be.
// 	MINUS = 0x4,					// The converted value is to be left adjusted on the field boundary.  (The default is right justification.)  The converted value is padded on the right with blanks, rather than on the left with blanks or zeros.  A - overrides a 0 if both are given.
// 	PLUS = 0x8,						// A sign (+ or -) should always be placed before a number produced by a signed conversion.  By default, a sign is used only for negative numbers.  A + overrides a space if both are used.
// 	SPACE = 0x10,					// (a space) A blank should be left before a positive number (or empty string) produced by a signed conversion.
// 	APOSTROPHE = 0x20,				// For decimal conversion (i, d, u, f, F, g, G) the output is to be grouped with thousands' grouping characters if the locale information indicates any.
// 	UPPERCASE_I = 0x40,				// ignored for now
// 	FLAGA = 0x80,					//
// 	FLAGB = 0x100,					//
// 	FLAGC = 0x200,					//
// 	FLAG1 = 0x400,					//
// 	FLAG2 = 0x800,					//
// 	FLAG3 = 0x1000,					//
// 	FLAG4 = 0x2000,					//
// 	FLAG5 = 0x4000,					//
// 	FLAG6 = 0x8000,					//
// }	t_print_flag;

void	ft_init_flags_helper(int flag, int *err, t_pf_info *data)
{
	if (data->flag & flag)
			*err = 1;
	else
		data->flag |= flag;
}

void	ft_init_flags(int *i, int *err, t_pf_info *data)
{
	while (data->orig[*i] && ft_strchr(F_FLAGS, data->orig[*i]))
	{
		if (data->orig[*i] == '0')
			ft_init_flags_helper(ZERO, err, data);
		else if (data->orig[*i] == '#')
			ft_init_flags_helper(HASHTAG, err, data);
		else if (data->orig[*i] == '-')
			ft_init_flags_helper(MINUS, err, data);
		else if (data->orig[*i] == '+')
			ft_init_flags_helper(PLUS, err, data);
		else if (data->orig[*i] == ' ')
			ft_init_flags_helper(SPACE, err, data);
		else if (data->orig[*i] == '\'')
			ft_init_flags_helper(APOSTROPHE, err, data);
		else if (data->orig[*i] == 'I')
			ft_init_flags_helper(UPPERCASE_I, err, data);
		++(*i);
	}
}

void	ft_init_field_width(int *i, int *err, t_pf_info *data, va_list arg)
{
	int	n;
	long long	num;

	if (data->orig[*i] == '*')
	{
		data->field_width = va_arg(arg, unsigned int);
		++(*i);
	}
	else
	{
		n = 0;
		num = ft_latoi(data->orig[*i]);
		while (ft_isdigit(data->orig[*i]))
		{
			++n;
			++(*i);
		}
		if (n > 15 || num > 0xFFFFFFFF)		//no need for crazy big precision.
			*err = 1;
		else
			data->precision = (unsigned int)num;
	}
}

void	ft_init_precision(int *i, int *err, t_pf_info *data, va_list arg)
{
	int			n;
	long long	num;

	if (data->orig[*i] == '*')
	{
		data->precision = va_arg(arg, unsigned int);
		++(*i);
	}
	else
	{
		n = 0;
		num = ft_latoi(data->orig[*i]);
		while (ft_isdigit(data->orig[*i]))
		{
			++n;
			++(*i);
		}
		if (n > 15 || num > 0xFFFFFFFF)		//no need for crazy big precision.
			*err = 1;
		else
			data->precision = (unsigned int)num;
	}
}

void	ft_init_modifiers(int *i, int *err, t_pf_info *data)
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
void ft_get_int_value_helper(t_pf_info *data, va_list arg, int flag)
{
	data->value_flag = flag;
	if (flag & SIGNED_CHAR)
		data->value.sc = va_arg(arg, signed char);
	else if (flag & SIGNED_SHORT)
		data->value.ss = va_arg(arg, signed short);
	else if (flag & LONG)
		data->value.l = va_arg(arg, long);
	else if (flag & LONG_LONG)
		data->value.ll = va_arg(arg, long long);
	else if (flag & SIZE_T)
		data->value.st = va_arg(arg, size_t);
	else if (flag & INT)
		data->value.i = va_arg(arg, int);
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
		else if (data->type_flag & LOWERCASE_Z)
			ft_get_int_value_helper(data, arg, SIZE_T);
		else
			return (1);
	}
	else
		ft_get_int_value_helper(data, arg, INT);
	return (0);
}

int	ft_init_int(char c, int i, t_pf_info *data, va_list arg)
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
void ft_get_unsigned_int_value_helper(t_pf_info *data, va_list arg, int flag)
{
	data->value_flag = flag;
	if (flag & UNSIGNED_CHAR)
		data->value.uc = va_arg(arg, unsigned char);
	else if (flag & UNSIGNED_SHORT)
		data->value.us = va_arg(arg, unsigned short);
	else if (flag & UNSIGNED_LONG)
		data->value.ul = va_arg(arg, unsigned long);
	else if (flag & UNSIGNED_LONG_LONG)
		data->value.ull = va_arg(arg, unsigned long long);
	else if (flag & SIZE_T)
		data->value.st = va_arg(arg, size_t);
	else if (flag & UNSIGNED_INT)
		data->value.ui = va_arg(arg, unsigned int);
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

int	ft_init_unsigned_unsigned_int(char c, int i, t_pf_info *data, va_list arg)
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

int	ft_init_double(char c, int i, t_pf_info *data, va_list arg)
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
	// update value from arg list;
}

int	ft_init_pointer(char c, int i, t_pf_info *data, va_list arg)
{
	if (data->type_flag & LENGTH_MODIFIER)
		return (1);
	if (c == 's')
	{
		data->type_flag |= LOWERCASE_S;
		data->value.s = va_arg(arg, char *);
	}
	else if (c == 'p')
	{
		data->type_flag |= LOWERCASE_P;
		data->value.p = va_arg(arg, void *);
	}
	return (0);
}

int	ft_init_covnversion(int i, t_pf_info *data, va_list arg)
{
	char	c;
	int		err;

	c = data->orig[i];
	err = 0;
	if (c == 'i' || c == 'd' || c == 'c')
		err = ft_init_int(c, i, data, arg);
	else if (c == 'o' || c == 'u' || c == 'x' || c == 'X'
		|| c == 'b' || c == 'B')
		err = ft_init_unsigned(c, i, data, arg);
	else if (c == 'e' || c == 'E' || c == 'f' || c == 'F'
		|| c == 'g' || c == 'G' || c == 'a' || c == 'A')
		err = ft_init_double(c, i, data, arg);
	else if (data->orig[i] == 's' || data->orig[i] == 'p')
		err = ft_init_pointer(c, i, data, arg);
	else if (data->orig[i] == 'C')
		data->type_flag |= UPPERCASE_C;
	else if (data->orig[i] == 'P')
		data->type_flag |= UPPERCASE_P;
	else if (data->orig[i] == '%')
		data->type_flag |= PERCENTAGE;
	else
		err = 1;
	return (err);
}

int	*ft_init_list(va_list arg, t_list *lst)
{
	t_pf_info	*data;
	int			i;
	int			err;

	i = 0;
	err = 0;
	while (lst)
	{
		data = lst->content;
		if (data->orig[i] && ft_strchr(F_FLAGS, data->orig[i]))
			ft_init_flags(&i, &err, data);
		if (data->orig[i] && ft_strchr(F_NUMBERS, data->orig[i]))
			ft_init_field_width(&i, &err, data, arg);
		if (data->orig[i] == '.')
		{
			++i;
			ft_init_precision(&i, &err, data, arg);
		}
		if (data->orig[i] && ft_strchr(F_MODIFIER, data->orig[i]))
			ft_init_modifiers(&i, &err, data);
		if (err || !ft_strchr(F_TYPES, data->orig[i])) // error
			return (1);
		if (ft_init_conversion(i, data, arg))
			return (1);
		lst = lst->next;
	}
	return (0);
}

char	*ft_get_print_string(va_list arg, const char *s)
{
	char	*str;
	t_list	*lst;

	lst = ft_process_string(s);
	str = NULL;
	ft_print_list(lst);  //just for testing and debugging.
	if (ft_init_list(arg, lst)) //checks for proper formating of the % sequences and returns non-zero value on error.
		free(lst); //should free the list properly.
	//fill list with arg stuff;
	//process list
	//join strings;
	//free everything except the str;

	//debug print list
	return (str);
}


//check if s?
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
