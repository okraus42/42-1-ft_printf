/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:59:58 by okraus            #+#    #+#             */
/*   Updated: 2023/10/08 12:59:35 by okraus           ###   ########.fr       */
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
	if (*err)	//REMOVE LATER
		printf("ERR FLAGS: %s\n", data->orig); //REMOVE LATER
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

	printf("WIDTH\n");
	if (data->orig[*i] == '*')
	{
		data->field_width = va_arg(arg, unsigned int);
		++(*i);
	}
	else
	{
		printf("WIDTH2\n");
		printf("%s\n", &data->orig[*i]);
		n = 0;
		num = ft_latoi(&data->orig[*i]);
		printf("num = %lli\n", num);
		while (ft_isdigit(data->orig[*i]))
		{
			++n;
			++(*i);
		}
		printf("n = %i\n", n);
		printf("err = %i\n", *err);
		if (n > 15 || num > 0xFFFFFFFF)		//no need for crazy big precision.
			*err = 1;
		else
			data->field_width = (unsigned int)num;
		printf("err2 = %i\n", *err);
		if (*err) //REMOVE LATER
			printf("ERR WIDTH: %s\n", data->orig); //REMOVE LATER
	}
}

void	ft_init_precision(int *i, int *err, t_pf_info *data, va_list arg)
{
	int			n;
	long long	num;

	write(1, "PRECISION\n", 10);
	data->flag |= PERIOD;
	if (data->orig[*i] == '*')
	{
		data->precision = va_arg(arg, unsigned int);
		++(*i);
	}
	else
	{
		printf("PRECISION2\n");
		n = 0;
		num = ft_latoi(&data->orig[*i]);
		while (ft_isdigit(data->orig[*i]))
		{
			++n;
			++(*i);
		}
		if (n > 15 || num > 0xFFFFFFFF)		//no need for crazy big precision.
			*err = 1;
		else if (num > 0)
			data->precision = (unsigned int)num;
		else
			data->precision = 0; //probably not needed
	}
	if (*err)//REMOVE LATER
		printf("ERR PRECISION: %s\n", data->orig); //REMOVE later
}

void	ft_init_modifiers(int *i, int *err, t_pf_info *data)
{
	(void)err; //possibly remove from the function later
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
		data->value.ll = (long long)va_arg(arg, int);//char promoted to int
	else if (flag & SIGNED_SHORT)
		data->value.ll = (long long)va_arg(arg, int);//short promoted to int
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
void ft_get_unsigned_int_value_helper(t_pf_info *data, va_list arg, int flag)
{
	data->value_flag = flag;
	if (flag & UNSIGNED_CHAR)
		data->value.ull = va_arg(arg, unsigned int); //char promoted to int
	else if (flag & UNSIGNED_SHORT)
		data->value.ull = va_arg(arg, unsigned int); //short promoted to int
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
		data->value.d = va_arg(arg, double); //float promoted to double
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
		err = ft_init_double(c,  data, arg);
	else if (data->orig[i] == 's' || data->orig[i] == 'p')
		err = ft_init_pointer(c,  data, arg);
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
				ft_init_flags(&i, &err, data);
			if (data->orig[i] && ft_strchr(F_NUMBERS, data->orig[i]))
				ft_init_field_width(&i, &err, data, arg);
			if (data->orig[i] == '.' && ft_strchr(F_NUMBERS, data->orig[i + 1]))
			{
				++i;
				ft_init_precision(&i, &err, data, arg);
			}
			if (data->orig[i] && ft_strchr(F_MODIFIER, data->orig[i]))
				ft_init_modifiers(&i, &err, data);
			if (err || !ft_strchr(F_TYPES, data->orig[i])) // error
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

char	*ft_get_print_string(va_list arg, const char *s)
{
	char	*str;
	t_list	*lst;

	lst = ft_process_input_string(s);
	str = NULL;
	//ft_print_list(lst);  //just for testing and debugging.
	if (ft_init_list(arg, lst))
	{ //checks for proper formating of the % sequences and returns non-zero value on error.
		printf("ERROR ERRROR ERRROR\nERRROR\nERROR ERRROR ERRROR\n");
		ft_print_list(lst);
		free(lst); //should free the list properly.
		lst = NULL;
	}
	//fill list with arg stuff;
	//process list
	if (ft_process_list(lst))
	{ //checks for proper formating of the % sequences and returns non-zero value on error.
		printf("ERROR PROCESS ERRROR\nERRROR\nERROR PROCESS ERRROR\n");
		ft_print_list(lst);
		free(lst); //should free the list properly.
		lst = NULL;
	}
	//join strings;
	str = ft_print_lst_to_string(lst);
	//free everything except the str;
	printf("FINAL STRING: %s\n", str);
	//debug print list
	if (lst)
		ft_print_list(lst); 
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
