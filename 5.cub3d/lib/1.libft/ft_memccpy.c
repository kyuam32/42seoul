/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:42:30 by nlee              #+#    #+#             */
/*   Updated: 2020/10/13 15:33:47 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	temp;
	size_t			i;

	i = 0;
	while (n-- > 0)
	{
		temp = ((unsigned char *)src)[i];
		((unsigned char *)dst)[i] = temp;
		i++;
		if (temp == (unsigned char)c)
			return ((void *)(dst + i));
	}
	return (0);
}
