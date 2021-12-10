/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 21:01:15 by nlee              #+#    #+#             */
/*   Updated: 2020/10/15 11:54:09 by nlee             ###   ########.fr       */
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
