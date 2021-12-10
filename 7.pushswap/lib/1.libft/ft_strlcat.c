/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:23:33 by nlee              #+#    #+#             */
/*   Updated: 2020/10/17 18:00:07 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dst_size)
{
	size_t dst_len;
	size_t src_len;
	size_t cpy_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_size < dst_len + 1)
		return (dst_size + src_len);
	if (dst_size > dst_len + src_len)
		cpy_len = src_len;
	else
		cpy_len = dst_size - dst_len - 1;
	ft_memcpy(dst + dst_len, src, cpy_len);
	dst[dst_len + cpy_len] = 0;
	return (dst_len + src_len);
}
