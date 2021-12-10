/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:15:26 by nlee              #+#    #+#             */
/*   Updated: 2020/10/13 15:36:08 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t i;

	if (!(dst) && !(src))
		return (0);
	i = 0;
	if (dst <= src)
	{
		while (n-- > 0)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
		while (n-- > 0)
			((unsigned char *)dst)[n] = ((unsigned char *)src)[n];
	return (dst);
}
