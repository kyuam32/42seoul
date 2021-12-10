/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parse_part_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkyu <namkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:45:34 by namkyu            #+#    #+#             */
/*   Updated: 2021/02/25 11:49:10 by namkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	flag_parse(const char *format, t_format_list *f_list)
{
	int		i;

	i = 0;
	while (format[i] == '-' || format[i] == '0')
	{
		if (format[i] == '-')
		{
			f_list->align = LEFT_ALIGN;
			f_list->zero_symbol = ' ';
		}
		else if (format[i] == '0' && !(ft_memchr(format, '-', i + 1)))
		{
			f_list->align = RIGHT_ALIGN;
			f_list->zero_symbol = '0';
		}
		i++;
	}
	return (i);
}

int	width_parse(const char *format, t_format_list *f_list, va_list *ap)
{
	int		i;

	i = 0;
	if (format[i] == '*')
	{
		f_list->width = va_arg(*ap, int);
		if (f_list->width < 0)
		{
			f_list->width = f_list->width * -1;
			f_list->align = LEFT_ALIGN;
			f_list->zero_symbol = ' ';
		}
		return (1);
	}
	f_list->width = ft_atoi(format);
	while (ft_isdigit(format[i]))
		i++;
	return (i);
}

int	precision_parse(const char *format, t_format_list *f_list, va_list *ap)
{
	int		i;

	i = 1;
	f_list->precision = 0;
	if (ft_isdigit(format[i]))
	{
		f_list->precision = ft_atoi(&format[i]);
		while (ft_isdigit(format[i]))
			i++;
	}
	else if (format[i] == '*')
	{
		f_list->precision = va_arg(*ap, int);
		if (f_list->precision < 0)
			f_list->precision = -1;
		i++;
	}
	return (i);
}

int	ft_printf_parsing_1(const char *format,
						t_format_list *f_list,
						va_list *ap,
						int *ret)
{
	int		i;

	i = 0;
	if (format[i] == '-' || format[i] == '0')
		i += flag_parse(&format[i], f_list);
	if (ft_isdigit(format[i]) || format[i] == '*')
		i += width_parse(&format[i], f_list, ap);
	if (format[i] == '.')
		i += precision_parse(&format[i], f_list, ap);
	*ret += ft_printf_parsing_2(&format[i], f_list, ap);
	return (i + 1);
}

int	ft_printf_parsing_2(const char *format, t_format_list *f_list, va_list *ap)
{
	int		printed_char_len;

	printed_char_len = 0;
	if (*format == 'd' || *format == 'i')
		printed_char_len = case_integer(f_list, ap);
	else if (*format == 'u' || *format == 'x' || *format == 'X')
		printed_char_len = case_undsigned_int(format, f_list, ap);
	else if (*format == 's')
		printed_char_len = case_string(f_list, ap);
	else if (*format == 'c' || *format == '%')
		printed_char_len = case_character(format, f_list, ap);
	else if (*format == 'p')
		printed_char_len = case_pointer(f_list, ap);
	reset_flist(f_list);
	return (printed_char_len);
}
