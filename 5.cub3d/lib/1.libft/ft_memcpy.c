/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:03:52 by nlee              #+#    #+#             */
/*   Updated: 2020/10/13 15:33:34 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	temp;
	size_t			i;

	if (!(dst) && !(src))
		return (0);
	i = 0;
	while (n-- > 0)
	{
		temp = ((unsigned char *)src)[i];
		((unsigned char *)dst)[i] = temp;
		i++;
	}
	return (dst);
}
