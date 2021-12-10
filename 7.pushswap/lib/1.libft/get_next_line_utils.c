/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:37:54 by nlee              #+#    #+#             */
/*   Updated: 2021/04/06 21:08:53 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	temp;
	size_t			i;

	if (!(dst) && !(src))
		return (0);
	i = 0;
	while (n-- > 0)
	{
		temp = ((unsigned char *)src)[i];
		((unsigned char *)dst)[i] = temp;
		i++;
	}
	return (dst);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	size_t src_len;
	size_t terminate_len;

	if (!(src) || !(dst))
		return (0);
	src_len = ft_strlen(src);
	if (dst_size)
	{
		if (src_len >= dst_size)
			terminate_len = dst_size - 1;
		else
			terminate_len = src_len;
		ft_memcpy(dst, src, terminate_len);
		dst[terminate_len] = 0;
	}
	return (src_len);
}

char	*ft_strdup(const char *str)
{
	char *ret;

	if (!(ret = (char *)malloc((ft_strlen(str) + 1) * sizeof(char))))
		return (0);
	ft_strlcpy(ret, str, ft_strlen(str) + 1);
	return (ret);
}

char	*ft_strjoin(char const *str1, char const *str2)
{
	size_t	str1_len;
	size_t	str2_len;
	char	*ret;

	if (!(str1))
		return (ft_strdup(str2));
	else if (!(str2))
		return (ft_strdup(str1));
	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	if (!(ret = (char *)malloc(sizeof(char) * (str1_len + str2_len + 1))))
		return (0);
	ft_strlcpy(ret, str1, str1_len + 1);
	ft_strlcpy(ret + str1_len, str2, str2_len + 1);
	return (ret);
}
