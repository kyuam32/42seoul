/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:33:17 by nlee              #+#    #+#             */
/*   Updated: 2020/10/15 11:53:46 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t str_len;
	size_t i;

	str_len = ft_strlen(str);
	i = 0;
	while (str_len - i != 0 && str[str_len - i] != (char)c)
		i++;
	if (str[str_len - i] == (char)c)
		return ((char *)(str + str_len - i));
	return (0);
}
