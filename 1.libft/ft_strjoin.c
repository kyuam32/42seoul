/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:15:53 by nlee              #+#    #+#             */
/*   Updated: 2020/10/17 12:26:28 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
