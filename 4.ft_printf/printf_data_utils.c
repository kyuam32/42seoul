/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_data_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 14:36:15 by namkyu            #+#    #+#             */
/*   Updated: 2021/02/23 18:59:55 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	num_data_input(unsigned long long num, t_format_list *f_list)
{
	int	i;

	i = 1;
	if (num == 0 && f_list->precision == 0)
		i = 0;
	while (num >= ft_strlen(f_list->base))
	{
		num = num / ft_strlen(f_list->base);
		i++;
	}
	f_list->strlen = i;
}

void	str_data_input(const char *str, t_format_list *f_list)
{
	if (f_list->precision == 0)
		f_list->strlen = 0;
	else if (ft_strlen(str) <= (size_t)f_list->precision || \
f_list->precision == -1)
	{
		f_list->strlen = ft_strlen(str);
		f_list->precision = -1;
	}
	else
		f_list->strlen = f_list->precision;
}
