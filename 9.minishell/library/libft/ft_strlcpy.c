/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:38:12 by nlee              #+#    #+#             */
/*   Updated: 2021/07/22 19:29:31 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	size_t	src_len;
	size_t	terminate_len;

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
