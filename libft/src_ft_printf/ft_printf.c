/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:59:58 by okraus            #+#    #+#             */
/*   Updated: 2023/09/30 18:00:27 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	ft_add_node(t_list **head, const char *s, int type, int *end)
{
	t_list		*lst;
	t_pf_info	*data;

	data = malloc(sizeof(t_pf_info));
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

t_list	*ft_process_string(va_list arg, const char *s)
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

char	*ft_get_print_string(va_list arg, const char *s)
{
	char	*str;
	t_list	*lst;

	lst = ft_process_string(arg, s);
	str = NULL;
	//create new list
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
