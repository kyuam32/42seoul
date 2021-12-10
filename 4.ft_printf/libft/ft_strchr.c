/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 15:38:03 by nlee              #+#    #+#             */
/*   Updated: 2020/10/13 16:28:12 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char *ret;

	if (c == 0)
		return ((char *)str + ft_strlen(str));
	ret = ft_memchr(str, c, ft_strlen(str));
	return (ret);
}
