/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlee <nlee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 16:47:24 by nlee              #+#    #+#             */
/*   Updated: 2020/10/19 21:47:09 by nlee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		cal_size(int n)
{
	int	count;

	count = 0;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char		*zero_case(void)
{
	char *ret;

	if (!(ret = (char *)malloc(sizeof(char) * 2)))
		return (0);
	ret[0] = '0';
	ret[1] = 0;
	return (ret);
}

static void		init_itoa(char *ret, int n, int num_len, int sign)
{
	if (sign == 1)
	{
		ret[0] = '-';
		ret++;
	}
	ret[num_len] = 0;
	while (n != 0)
	{
		num_len--;
		if (n < 0)
		{
			ret[num_len] = '0' - (n % 10);
		}
		else
			ret[num_len] = n % 10 + '0';
		n = n / 10;
	}
}

char			*ft_itoa(int n)
{
	char	*ret;
	int		sign;
	int		num_len;

	if (n == 0)
		return (zero_case());
	else if (n < 0)
		sign = 1;
	else
		sign = 0;
	num_len = cal_size(n);
	if (!(ret = (char *)malloc(sizeof(char) * num_len + sign + 1)))
		return (0);
	init_itoa(ret, n, num_len, sign);
	return (ret);
}
