/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 12:28:20 by nlee              #+#    #+#             */
/*   Updated: 2020/10/17 16:03:13 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	trim_start;
	size_t	trim_end;

	if (!(s1))
		return (NULL);
	if (!(set))
		return (ft_strdup(s1));
	trim_start = 0;
	trim_end = 0;
	while (ft_memchr(set, s1[trim_start], ft_strlen(set)))
		trim_start++;
	trim_end = ft_strlen(s1);
	if (trim_start >= trim_end)
		return (ft_strdup(""));
	while (ft_memchr(set, s1[trim_end - 1], ft_strlen(set)))
		trim_end--;
	if (!(ret = (char *)malloc(sizeof(char) * (trim_end - trim_start + 1))))
		return (0);
	ft_strlcpy(ret, &s1[trim_start], trim_end - trim_start + 1);
	return (ret);
}
