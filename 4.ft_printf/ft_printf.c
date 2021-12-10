/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:05:07 by namkyu            #+#    #+#             */
/*   Updated: 2021/03/01 15:47:49 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reset_flist(t_format_list *f_list)
{
	f_list->zero_len = 0;
	f_list->zero_symbol = ' ';
	f_list->width = 0;
	f_list->align = RIGHT_ALIGN;
	f_list->precision = -1;
	f_list->strlen = 0;
	f_list->sign = 0;
	f_list->base = TYPE_STRING;
}

int		ft_printf(const char *format, ...)
{
	t_format_list	*f_list;
	va_list			ap;
	int				ret;

	ret = 0;
	va_start(ap, format);
	reset_flist(f_list);
	while (*format)
	{
		if (*format != '%')
		{
			write(1, format, 1);
			ret++;
		}
		else
			format += ft_printf_parsing_1(format + 1, f_list, &ap, &ret);
		format++;
	}
	va_end(ap);
	return (ret);
}
