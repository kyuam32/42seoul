/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongklee <dongklee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 12:28:20 by nlee              #+#    #+#             */
/*   Updated: 2021/07/22 19:29:31 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char a, char const *set)
{
	size_t	idx;

	idx = 0;
	while (set[idx])
	{
		if (a == set[idx])
			return (1);
		idx++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	char	*front;
	char	*back;
	size_t	len;

	if (!s1 || !set)
		return (0);
	front = (char *)s1;
	back = front + ft_strlen(s1);
	while (*front && is_in_set(*front, set))
		front++;
	while ((front < back) && is_in_set(*(back - 1), set))
		back--;
	len = (back - front) + 1;
	result = (char *)malloc(sizeof(char) * len);
	if (!(result))
		return (0);
	ft_strlcpy(result, front, len);
	return (result);
}
