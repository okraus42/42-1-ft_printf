/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:36:53 by okraus            #+#    #+#             */
/*   Updated: 2023/10/06 16:47:52 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

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
	printf("STRJOINFREEBOTH: %s\n", s3);
	return (s3);
}