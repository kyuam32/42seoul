/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 14:15:11 by nlee              #+#    #+#             */
/*   Updated: 2020/10/19 13:14:57 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*skip_char(char *src, char c, int delimiter)
{
	if (delimiter == 0)
	{
		while (*src != c && *src)
			src++;
		return (src);
	}
	else if (delimiter == 1)
	{
		while (*src == c && *src)
			src++;
		return (src);
	}
	else
		return (0);
}

static size_t	count_str(char *str, char c)
{
	size_t count;
	size_t i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] != c && str[i + 1] == c) ||\
				(str[i] != c && str[i + 1] == 0))
			count++;
		i++;
	}
	return (count);
}

static char		**mal_free(char **ret)
{
	size_t i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		i++;
	}
	free(ret[i]);
	return (0);
}

static void		init_split(char **ret, size_t i, char *str_start, char *str_end)
{
	if (!(ret[i] = (char *)malloc(sizeof(char) *\
					(str_end - str_start + 1))))
		mal_free(ret);
	ft_strlcpy(ret[i], str_start, str_end - str_start + 1);
}

char			**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	i;
	size_t	str_num;
	char	*str_start;
	char	*str_end;

	if (!s)
		return (0);
	str_num = count_str((char *)s, c);
	if (!(ret = (char **)malloc(sizeof(char *) * (str_num + 1))))
		return (0);
	i = 0;
	str_start = (char *)s;
	while (i < str_num)
	{
		str_start = skip_char(str_start, c, 1);
		str_end = skip_char(str_start, c, 0);
		init_split(ret, i, str_start, str_end);
		str_start = str_end;
		i++;
	}
	ret[i] = 0;
	return (ret);
}
