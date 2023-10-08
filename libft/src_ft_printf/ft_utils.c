/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:36:53 by okraus            #+#    #+#             */
/*   Updated: 2023/10/08 15:55:46 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	ft_lnumlen_base(long long n, int base)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}

char	*ft_ltoa_base(long long n, char *basestr, int baselen)
{
	char				*str;
	int					i;
	unsigned long long	m;

	if (baselen > (int)ft_strlen(basestr) || baselen < 2)
		return (NULL);
	i = ft_lnumlen_base(n, baselen) - 1;
	str = (char *)malloc((i + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[i + 1] = 0;
	if (n == 0)
		str[i] = basestr[0];
	if (n < 0)
	{
		str[0] = '-';
		m = -n;
	}
	else
		m = n;
	while (m != 0)
	{
		str[i] = basestr[m % baselen];
		m = m / baselen;
		i--;
	}
	return (str);
}

static int	ft_ulnumlen_base(unsigned long long n, int base)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}

char	*ft_ultoa_base(unsigned long long n, char *basestr, int baselen)
{
	char	*str;
	int		i;

	if (baselen > (int)ft_strlen(basestr) || baselen < 2)
		return (NULL);
	i = ft_ulnumlen_base(n, baselen) - 1;
	str = (char *)malloc((i + 2) * sizeof(char));
	//printf("ub1: %p\n", str);
	if (str == NULL)
		return (NULL);
	str[i + 1] = 0;
	if (n == 0)
		str[i] = basestr[0];
	while (n != 0)
	{
		str[i] = basestr[n % baselen];
		n = n / baselen;
		i--;
	}
	//printf("ub2: %p\n", str);
	return (str);
}

char	*ft_string_copy_n(char const *str, int n)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_strlen(str);
	if (n < len)
		len = n;
	if (!str)
		return (NULL);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}


char	*ft_strjoin_freeright(char const *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*s3;

	j = ft_strlen(s1);
	i = ft_strlen(s2);
	s3 = (char *)malloc((i + j + 1) * sizeof(char));
	if (s3 == NULL)
	{
		free (s2);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		s3[i + j] = s2[i];
		i++;
	}
	s3[i + j] = 0;
	free(s2);
	return (s3);
}

char	*ft_strjoin_freeleft(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*s3;

	j = ft_strlen(s1);
	i = ft_strlen(s2);
	s3 = (char *)malloc((i + j + 1) * sizeof(char));
	if (s3 == NULL)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		s3[i + j] = s2[i];
		i++;
	}
	s3[i + j] = 0;
	free(s1);
	return (s3);
}

char	*ft_strjoin_freeboth(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*s3;

	j = ft_strlen(s1);
	i = ft_strlen(s2);
	s3 = malloc((i + j + 1) * sizeof(char));
	if (s3 == NULL)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		s3[i + j] = s2[i];
		i++;
	}
	s3[i + j] = 0;
	free(s1);
	free(s2);
	// printf("STRJOINFREEBOTH: %s\n", s3);
	return (s3);
}

// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	t_list	*tmp;

// 	if (lst)
// 	{
// 		while (*lst)
// 		{
// 			tmp = (*lst)->next;
// 			ft_lstdelone(*lst, del);
// 			(*lst) = tmp;
// 		}
// 	}
// 	lst = NULL;
// }

void	ft_clear_pf_data(void *vdata)
{
	t_pf_info *data;

	data = vdata;
	//printf("free: %p\n", data->out);
	if (data->out)
		free(data->out);
	data->out = NULL;
	free(data);
	data = NULL;
}