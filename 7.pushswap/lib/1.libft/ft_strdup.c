/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 21:01:15 by nlee              #+#    #+#             */
/*   Updated: 2021/04/30 16:26:15 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char *ret;

	if (!(ret = (char *)malloc((ft_strlen(str) + 1) * sizeof(char))))
		return (0);
	ft_strlcpy(ret, str, ft_strlen(str) + 1);
	return (ret);
}
