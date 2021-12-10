/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:13:20 by nlee              #+#    #+#             */
/*   Updated: 2020/10/13 15:32:42 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *src1, const void *src2, size_t n)
{
	size_t i;

	i = 0;
	while (n-- > 0)
	{
		if (((unsigned char *)src1)[i] != ((unsigned char *)src2)[i])
			return (((unsigned char *)src1)[i] - ((unsigned char *)src2)[i]);
		i++;
	}
	return (0);
}
