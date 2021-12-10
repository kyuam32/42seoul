/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 12:16:57 by nlee              #+#    #+#             */
/*   Updated: 2020/10/17 16:01:19 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	i;
	size_t			src_len;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (src_len <= start)
		return (ft_strdup(""));
	if (start < 0)
		start = src_len + start;
	if (!(ret = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (len-- > 0)
		ret[i++] = s[start++];
	ret[i] = 0;
	return (ret);
}
