/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:07:29 by nlee              #+#    #+#             */
/*   Updated: 2020/10/13 15:34:22 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	size_t i;

	i = 0;
	while (n-- > 0)
	{
		if (((unsigned char *)src)[i] == (unsigned char)c)
			return ((void *)(src + i));
		i++;
	}
	return (0);
}
