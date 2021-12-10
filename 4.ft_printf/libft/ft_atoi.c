/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:27:02 by nlee              #+#    #+#             */
/*   Updated: 2020/11/03 14:53:57 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_isspace(int c)
{
	if ((unsigned char)c == '\t')
		return (1);
	else if ((unsigned char)c == '\n')
		return (1);
	else if ((unsigned char)c == '\v')
		return (1);
	else if ((unsigned char)c == '\f')
		return (1);
	else if ((unsigned char)c == '\r')
		return (1);
	else if ((unsigned char)c == ' ')
		return (1);
	return (0);
}

int				ft_atoi(const char *str)
{
	size_t	ret;
	int		sign;
	size_t	i;

	ret = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		ret = (ret * 10) + (str[i] - '0');
		i++;
	}
	if (sign > 0 && ret > LONG_MAX)
		return (-1);
	else if (sign < 0 && ret - 1 > LONG_MAX)
		return (0);
	return (sign * (int)ret);
}
