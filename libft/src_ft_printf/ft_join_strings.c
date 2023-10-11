/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_strings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:22:52 by okraus            #+#    #+#             */
/*   Updated: 2023/10/11 16:48:57 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static char	*ft_strjoin_printf(char *s1, t_pf_info *data, int len)
{
	int	i;
	int	j;
	char	*s3;

	j = len;
	i = data->outlen;
	//printf("s1 = %s\n", s1);
	//printf("out= %s\n", data->out);
	s3 = (char *)malloc((i + j + 1) * sizeof(char));
	if (s3 == NULL)
		return (free(s1), NULL);
	s3[i + j] = 0;
	j = 0;
	while (j < len)
	{
		s3[j] = s1[j];
		//printf("s3.  = %s, j = %i\n", s3, j);
		j++;
	}
	i = 0;
	while (i < data->outlen)
	{
		s3[i + j] = data->out[i];
		//printf("s3..  = %s, j = %i, i = %i\n", s3, j, i);
		//printf("s3.. = %s\n", s3);
		i++;
	}
	s3[i + j] = 0;
	//printf("s3 = %s\n", s3);
	return (free(s1), s3);
}

// need special strjoin for 0 characters
char	*ft_print_lst_to_string(t_list *lst, int *len)
{
	t_pf_info	*data;
	char		*str;

	str = ft_strdup("");
	while (lst)
	{
		if (!str)
			return (NULL);
		data = lst->content;
		//printf("data->out: %s\n", data->out);
		//printf("data->outlen: %i\n", data->outlen);
		
		if (data->out)
			str = ft_strjoin_printf(str, data, *len);
		*len += data->outlen;
		lst = lst->next;
	}
	return (str);
}
