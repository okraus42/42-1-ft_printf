/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:59:58 by okraus            #+#    #+#             */
/*   Updated: 2023/10/13 17:51:04 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

// void	ft_print_list(t_list *lst)
// {
// 	t_pf_info	*data;

// 	while (lst)
// 	{
// 		data = lst->content;
// 		if (data)
// 		{
// 			if (data->orig)
// 			{
// 				printf("string: %s\n", data->orig);
// 			}
// 			else
// 				write(1, "string not found", 16);
// 			printf("data type: %i\n", data->type);
// 			printf("flag: %x\n", data->flag);
// 			printf("value_flag: %x\n", data->value_flag);
// 			printf("type_flag: %x\n", data->type_flag);
// 			printf("value: %i\n", data->value.i);
// 			printf("width: %x\n", data->field_width);
// 			printf("precision: %x\n", data->precision);
// 		}
// 		else
// 			write(1, "data not found\n", 15);
// 		lst = lst->next;
// 	}
// }

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
